#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "image.hpp"
#include "player.hpp"
#include "scene.hpp"
#include "mat.hpp"
#include "camera.hpp"


class app{

    public:
        app();
        void Draw();
        void PreDraw();
        void InitializeProgram();
        void MainLoop();
        void Run();
        void CleanUp();
        void Input();
        GLuint CompileShader(GLuint type, const GLchar* source);
        GLchar* LoadShaderSource(const char *filename);
        GLuint CreateShaderProgram(const char* vertexshadersource, const char* fragementshadersource);
        void CreateGraphicsPipeline();
        void VertexSpecification();

    private:
        int gScreenWidth = 1200;
        int gScreenHeight = 800;
        SDL_Window* gGraphicsApplicationWindow = nullptr;
        SDL_GLContext gOpenGlContext = nullptr;

        bool gQuit = false;

        GLuint gVertexArrayObject = 0;
        GLuint gVertexBufferObject = 0;
        GLuint gIndexBufferObject = 0;
        GLuint gGraphicsPipelineShaderProgram = 0;
        //image myImage;

        GLfloat gAspectRatio = 0.0f;

        Scene myScene;
        int input = 0;

};