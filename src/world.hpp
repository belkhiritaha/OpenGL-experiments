#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "cube.hpp"

class World {
    public:
        World();
        ~World();
        std::vector<GLfloat> vertexData;

        void addVertex(std::vector<GLfloat> vertex);
        void addTriangle(std::vector<GLfloat> v1, std::vector<GLfloat> v2, std::vector<GLfloat> v3);
        void addQuad(std::vector<GLfloat> t1v1, std::vector<GLfloat> t1v2, std::vector<GLfloat> t1v3, std::vector<GLfloat> t2v1, std::vector<GLfloat> t2v2, std::vector<GLfloat> t2v3);
        void addCube(std::vector<GLfloat> center, GLfloat size);
        void addPlane(std::vector<GLfloat> center, GLfloat size, int width, int height);
        void removeQuad(std::vector<GLfloat> t1v1, std::vector<GLfloat> t1v2, std::vector<GLfloat> t1v3, std::vector<GLfloat> t2v1, std::vector<GLfloat> t2v2, std::vector<GLfloat> t2v3);

        std::vector<Cube> cubes;
};