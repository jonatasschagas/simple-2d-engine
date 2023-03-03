/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "OpenGLHeaders.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.hpp"
#include "Shader.hpp"

#include <glad/glad.h> 

#include <string>
#include <map>

using namespace std;

class SpriteRenderer
{
public:
    SpriteRenderer();
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Shader &shader);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), glm::vec4 textureCoordinates = glm::vec4(0,0,0,0), float rotate = 0.0f);
private:
    
    void createQuadVAO(string quadName, glm::vec2 textureSize, glm::vec4 textureCoordinates);
    
    // Render state
    Shader&       shader; 
    unsigned int quadVAO;
    map<string, unsigned int> m_quadVAOs;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif