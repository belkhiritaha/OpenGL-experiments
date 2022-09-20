#include "chunk.hpp"

namespace ChunkData {
    int chunkSize = 8;
}

Chunk::Chunk()
{
    // init blocks
    this->blocks = new int**[ChunkData::chunkSize];
    for (int i = 0; i < ChunkData::chunkSize; i++) {
        this->blocks[i] = new int*[ChunkData::chunkSize];
        for (int j = 0; j < ChunkData::chunkSize; j++) {
            this->blocks[i][j] = new int[ChunkData::chunkSize];
            for (int k = 0; k < ChunkData::chunkSize; k++) {
                this->blocks[i][j][k] = 0;
            }
        }
    }
    std::cout << "Chunk created" << std::endl;
}

Chunk::~Chunk()
{

}


int Chunk::GetPosX()
{
    return this->chunkPosX;
}

int Chunk::GetPosY()
{
    return this->chunkPosY;
}

void Chunk::SetPosX(int x)
{
    this->chunkPosX = x;
}

void Chunk::SetPosY(int y)
{
    this->chunkPosY = y;
}

void Chunk::addCube(Cube cube)
{
    GLfloat size = blocks::size;
    int x = cube.center[0]/size;
    int y = cube.center[1]/size;
    int z = cube.center[2]/size;

    blocks[x - ChunkData::chunkSize * GetPosX()][y][z- ChunkData::chunkSize * GetPosY()] = 1;

    std::cout << "Added block at " << x - ChunkData::chunkSize * GetPosX() << " " << y << " " << z - ChunkData::chunkSize * GetPosY() << std::endl;
}