#include "OpenGLRenderer.h"

#include "view/Game.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

OpenGLRenderer openGLRenderer;

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);  // clear frame buffer (also called the color buffer)
    
    openGLRenderer.pGame->render();
    
    glFlush();         // Render (draw) the object
    glutSwapBuffers(); // Swap buffers in double buffering.
}

void resizeWindow(int w, int h)
{
    glViewport(0, 0, w, h);           // Viewport within the graphics window.

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);

    openGLRenderer.screenWidth = w;
    openGLRenderer.screenHeight = h;
}

void update()
{
    float currentTimeSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float deltaTime = currentTimeSeconds - openGLRenderer.previousTimeSeconds;
    openGLRenderer.previousTimeSeconds = currentTimeSeconds;

    openGLRenderer.pGame->update(deltaTime);
	glutPostRedisplay();
}

void initialize(int argc, char **argv, Game* pGame, int screenWidth, int screenHeight)
{
    assert (pGame != nullptr);

    openGLRenderer.pGame = pGame;
    openGLRenderer.screenWidth = screenWidth;
    openGLRenderer.screenHeight = screenHeight;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double-buffering and RGB color mode.
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow(openGLRenderer.pGame->getGameName().c_str());

    glutDisplayFunc(render);

    glutReshapeFunc(resizeWindow);

    // glutMouseFunc(mouse);  // for mouse 
    // glutKeyboardFunc(key); // for keyboard 
    
    glutIdleFunc(update);

    glClearColor(0.0, 0.0, 0.0, 0.0); 

    glutMainLoop();
}
