
#include "OpenGLRenderer.h"
#include "SampleGame.hpp"

int main(int argc, char **argv)
{
    SampleGame sampleGame;
    
    initialize(argc, argv, &sampleGame, 800, 600);
    
    return 0;
}
