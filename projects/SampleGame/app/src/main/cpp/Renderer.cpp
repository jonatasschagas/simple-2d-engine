#include "Renderer.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <GLES3/gl3.h>
#include <memory>
#include <vector>
#include <android/imagedecoder.h>
#include <time.h>

#include "SampleGame.hpp"
#include "OpenGLGraphicsManager.hpp"
#include "sound/impl/MuteSoundManager.hpp"
#include "AndroidInputManager.hpp"
#include "AndroidOut.h"
#include "Utility.h"
#include "AndroidResourceProvider.h"

//! executes glGetString and outputs the result to logcat
#define PRINT_GL_STRING(s) {aout << #s": "<< glGetString(s) << std::endl;}

/*!
 * @brief if glGetString returns a space separated list of elements, prints each one on a new line
 *
 * This works by creating an istringstream of the input c-style string. Then that is used to create
 * a vector -- each element of the vector is a new element in the input string. Finally a foreach
 * loop consumes this and outputs it to logcat using @a aout
 */
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
aout << #s":\n";\
for (auto& extension: extensionList) {\
    aout << extension << "\n";\
}\
aout << std::endl;\
}

Renderer::~Renderer() {
    if (m_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_display, m_context);
            m_context = EGL_NO_CONTEXT;
        }
        if (m_surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_display, m_surface);
            m_surface = EGL_NO_SURFACE;
        }
        eglTerminate(m_display);
        m_display = EGL_NO_DISPLAY;
    }

    delete m_pSampleGame;
    delete m_pGraphicsManager;
    delete m_pResourceProvider;
    delete m_pMuteSoundManager;
    delete m_pInputManager;

    initializeMembers();
}

void Renderer::render() {
    // Check to see if the surface has changed size. This is _necessary_ to do every frame when
    // using immersive mode as you'll get no other notification that your renderable area has
    // changed.
    updateRenderArea();

    // clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    double now = getNowMs();
    double delta = (now - m_previousFrameMs)/1000.f;

    m_pSampleGame->update(delta);
    m_pSampleGame->render();

    m_previousFrameMs = now;

    // Present the rendered image. This is an implicit glFlush.
    auto swapResult = eglSwapBuffers(m_display, m_surface);
    assert(swapResult == EGL_TRUE);
}

void Renderer::initRenderer() {

    // Choose your render attributes
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                         << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    aout << "Found " << numConfigs << " configs" << std::endl;
    aout << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, m_pApp->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);
    assert(madeCurrent);

    m_display = display;
    m_surface = surface;
    m_context = context;

    // make width and height invalid so it gets updated the first frame in @a updateRenderArea()
    m_width = -1;
    m_height = -1;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::updateRenderArea() {
    EGLint width;
    eglQuerySurface(m_display, m_surface, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &height);

    if (width != m_width || height != m_height) {
        m_width = width;
        m_height = height;
        glViewport(0, 0, width, height);

        AAssetManager* pAssetManager = m_pApp->activity->assetManager;
        m_pResourceProvider = new AndroidResourceProvider(pAssetManager);

        m_pGraphicsManager = new OpenGLGraphicsManager(m_width, m_height, 100, 1, 1, *m_pResourceProvider);
        m_pGraphicsManager->loadShader("textured", "assets/shaders/android/sprite.vs", "assets/shaders/android/sprite.frag", *m_pResourceProvider);
        m_pGraphicsManager->loadShader("colored", "assets/shaders/android/color.vs", "assets/shaders/android/color.frag", *m_pResourceProvider);
        m_pGraphicsManager->loadShader("circle", "assets/shaders/android/circle.vs", "assets/shaders/android/circle.frag", *m_pResourceProvider);
        m_pGraphicsManager->initialize();

        m_pMuteSoundManager = new MuteSoundManager();
        m_pInputManager = new AndroidInputManager(m_pApp);

        m_pSampleGame = new SampleGame(*m_pGraphicsManager,
                                       *m_pMuteSoundManager,
                                       *m_pInputManager);
        m_pSampleGame->initialize();
    }
}

void Renderer::handleInput() {
    if (m_pInputManager != nullptr)
        m_pInputManager->pollEvents();
}

double Renderer::getNowMs()
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
}