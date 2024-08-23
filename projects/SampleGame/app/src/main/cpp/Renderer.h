#ifndef RENDERER_H
#define RENDERER_H

#include <EGL/egl.h>

struct android_app;
class MuteSoundManager;
class OpenGLGraphicsManager;
class ResourceProvider;
class InputManager;
class SampleGame;

class Renderer {
public:
    /*!
     * @param pApp the android_app this Renderer belongs to, needed to configure GL
     */
    inline Renderer(android_app *pApp) :
            m_pApp(pApp),
            m_display(EGL_NO_DISPLAY),
            m_surface(EGL_NO_SURFACE),
            m_context(EGL_NO_CONTEXT),
            m_width(0),
            m_height(0){
        initializeMembers();
        initRenderer();
    }

    virtual ~Renderer();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initRenderer();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    double getNowMs();

    android_app* m_pApp;
    EGLDisplay m_display;
    EGLSurface m_surface;
    EGLContext m_context;
    EGLint m_width;
    EGLint m_height;

    SampleGame* m_pSampleGame;
    OpenGLGraphicsManager* m_pGraphicsManager;
    MuteSoundManager* m_pMuteSoundManager;
    ResourceProvider* m_pResourceProvider;
    InputManager* m_pInputManager;
    double m_previousFrameMs;

    void initializeMembers()
    {
        m_pSampleGame = nullptr;
        m_pGraphicsManager = nullptr;
        m_pMuteSoundManager = nullptr;
        m_pInputManager = nullptr;
        m_pResourceProvider = nullptr;
        m_previousFrameMs = 0;
    }

};

#endif //RENDERER_H