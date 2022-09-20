#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "cube.hpp"
#include "chunk.hpp"
#include "chunk.hpp"
#include "camera.hpp"

class World {
    public:
        World();
        ~World();
        std::vector<GLfloat> vertexData;
        std::vector<GLuint> indexData;

        void addVertex(std::vector<GLfloat> vertex, GLfloat texture_x, GLfloat texture_y);
        void addTriangle(std::vector<GLfloat> v1, std::vector<GLfloat> v2, std::vector<GLfloat> v3);
        void addQuad(std::vector<GLfloat> point1, std::vector<GLfloat> point2, std::vector<GLfloat> point3, std::vector<GLfloat> point4);
        void addCube(std::vector<GLfloat> center, GLfloat size);
        void addPlane(std::vector<GLfloat> center, GLfloat size, int width, int height, GLfloat noise);
        void removeQuad(std::vector<GLfloat> t1v1, std::vector<GLfloat> t1v2, std::vector<GLfloat> t1v3, std::vector<GLfloat> t2v1, std::vector<GLfloat> t2v2, std::vector<GLfloat> t2v3);
        void addIndex(std::vector<int> index);

        GLfloat noise(std::vector<GLfloat> center, GLfloat size);
        GLfloat dotGridGradient(int ix, int iy, GLfloat x, GLfloat y);
        GLfloat lerp(GLfloat a, GLfloat b, GLfloat f);

        void printIndexData();
        void printVertexData();
        std::vector<Cube> cubes;

        Chunk *** chunks;
        void initChunks(int n);
        std::vector<int> getBlockChunk(std::vector<GLfloat> center);

        Camera myCamera;
};