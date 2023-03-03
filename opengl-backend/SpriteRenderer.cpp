/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"

#include "utils/StringUtils.h"

SpriteRenderer::SpriteRenderer() : shader(ResourceManager::GetShader("sprite"))
{}

SpriteRenderer::SpriteRenderer(Shader &shader) : shader(shader)
{
    //this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
    for (auto& pair : m_quadVAOs)
    {
        glDeleteVertexArrays(1, &pair.second);
    }
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, glm::vec4 textureCoordinates, float rotate)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);

    // render textured quad
    
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    string quadName = stringFormat("%d-%f-%f-%f-%f", texture.ID, textureCoordinates.x, textureCoordinates.y, textureCoordinates.z, textureCoordinates.w);
    if (m_quadVAOs.find(quadName) == m_quadVAOs.end())
    {
        createQuadVAO(quadName, glm::vec2(texture.Width, texture.Height), textureCoordinates);
    }
    unsigned int quadVAO = m_quadVAOs[quadName];

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::createQuadVAO(string quadName, glm::vec2 textureSize, glm::vec4 textureCoordinates)
{
    float xs = textureCoordinates.x/textureSize.x; // x start
    float xe = (textureCoordinates.x + textureCoordinates.w)/textureSize.x; // x end
    float ys = textureCoordinates.y/textureSize.y; // y start
    float ye = (textureCoordinates.y + textureCoordinates.z)/textureSize.y; // y end
    
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, xs, ye,
        1.0f, 0.0f, xe, ys,
        0.0f, 0.0f, xs, ys, 

        0.0f, 1.0f, xs, ye,
        1.0f, 1.0f, xe, ye,
        1.0f, 0.0f, xe, ys
    };
    
    unsigned int quadVAO;

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_quadVAOs.insert(std::pair<string, unsigned int>(quadName, quadVAO));
}
