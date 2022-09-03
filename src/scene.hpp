#pragma once
#include "player.hpp"
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include "mat.hpp"
#include "blocks.hpp"

class Scene
{
    public:
        Scene();
        ~Scene();
        void Update();
        Player myPlayer;
        // Obj ?
        std::vector<GLfloat> vertexData = {};
        std::vector<GLuint> indexBufferData = {};
        void addCube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, blocks::colorsList colors);
        void addPlane(GLint sizeHorz, GLint sizeVert, GLfloat x, GLfloat y, GLfloat z, blocks::colorsList colors);

};