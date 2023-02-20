#include "SampleGame.hpp"

#ifdef __APPLE__  // include Mac OS X verions of headers
#include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#include <GL/glut.h>
#endif

SampleGame::SampleGame() : Game()
{
    initializeMembers();
}

SampleGame::~SampleGame()
{
    initializeMembers();
}

void SampleGame::initialize(PlatformManager* pManager)
{

}

void SampleGame::receiveEvent(Event* pEvent)
{

}

void SampleGame::update(const float deltaTime)
{

}

void SampleGame::updateEditor(const float deltaTime)
{

}

void SampleGame::render()
{
    glColor3f(0.0, 1.0, 1.0);      // draw in cyan.
                                   // The color stays the same until we
                                   // change it next time.

    glBegin(GL_POLYGON);           // Draw a polygon (can have many vertices)
                                   // The vertex coordinates change by different
                                   // values of f; see also function idle().
    glVertex2f(100, 100); 
    glVertex2f(200, 100);
    glVertex2f(200, 300);
    glVertex2f(100, 300);
    glEnd();
}

const string& SampleGame::getGameName()
{
    return m_gameName;
}
