#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>



class image{
    public:
        image();
        GLuint CompileShader(GLuint type, const GLchar* source);
        GLchar* LoadShaderSource(const char *filename);
        GLuint CreateShaderProgram(const char* vertexshadersource, const char* fragementshadersource);
        void CreateGraphicsPipeline();
        void VertexSpecification();
        void Run();
        GLuint gVertexArrayObject = 0;
        GLuint gVertexBufferObject = 0;
        GLuint gGraphicsPipelineShaderProgram = 0;

};