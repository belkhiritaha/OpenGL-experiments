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
        int chunkPosX;
        int chunkPosY;
        int *** blocks;

        void SetPosX(int x);
        void SetPosY(int y);
        int GetPosX();
        int GetPosY();
        void addCube(Cube cube);
};


namespace ChunkData {
    extern int chunkSize;
}