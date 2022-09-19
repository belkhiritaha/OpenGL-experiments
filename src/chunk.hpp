#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>

#include "cube.hpp"
#include "blocks.hpp"

class Chunk {
    public:
        Chunk();
        ~Chunk();
        int chunkSize = 8;
        int *** blocks;

        void addCube(Cube cube);
};