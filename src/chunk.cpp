#include "chunk.hpp"



Chunk::Chunk()
{
    // init blocks
    this->blocks = new int**[chunkSize];
    for (int i = 0; i < chunkSize; i++) {
        this->blocks[i] = new int*[chunkSize];
        for (int j = 0; j < chunkSize; j++) {
            this->blocks[i][j] = new int[chunkSize];
            for (int k = 0; k < chunkSize; k++) {
                this->blocks[i][j][k] = 0;
            }
        }
    }
    std::cout << "Chunk created" << std::endl;
}

Chunk::~Chunk()
{

}


void Chunk::addCube(Cube cube)
{
    GLfloat size = blocks::size;
    int x = cube.center[0]/size;
    int y = cube.center[1]/size;
    int z = cube.center[2]/size;

    this->blocks[x][y][z] = 1;

    std::cout << "Added block at " << x << " " << y << " " << z << std::endl;
}