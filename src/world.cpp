#include "world.hpp"

World::World()
{
    std::cout << "World created" << std::endl;
    vertexData = {};
    chunks.push_back(new Chunk());
}

World::~World()
{
    std::cout << "World destroyed" << std::endl;
    // destroy cubes
    for (int i = 0; i < cubes.size(); i++)
    {
        delete &cubes[i];
    }
}


void World::printVertexData()
{
    std::cout << "Vertex data: " << std::endl;
    for (int i = 0; i < vertexData.size(); i++)
    {
        std::cout << vertexData[i] << std::endl;
    }
}


void World::printIndexData()
{
    std::cout << "Index data: " << std::endl;
    for (int i = 0; i < indexData.size(); i++)
    {
        std::cout << indexData[i] << std::endl;
    }
}


void World::addIndex(std::vector<int> index)
{
    indexData.push_back(index[0]);
    indexData.push_back(index[1]);
    indexData.push_back(index[2]);
}


void World::addVertex(std::vector<GLfloat> vertex, GLfloat texture_x, GLfloat texture_y)
{
    vertexData.push_back(vertex[0]);
    vertexData.push_back(vertex[1]);
    vertexData.push_back(vertex[2]);

    // vertexData.push_back(texture_x);
    // vertexData.push_back(texture_y);
}


void World::addTriangle(std::vector<GLfloat> v1, std::vector<GLfloat> v2, std::vector<GLfloat> v3){
    addVertex(v1, 0.0f, 1.0f);
    addVertex(v2, 0.0f, 0.0f);
    addVertex(v3, 1.0f, 0.0f);
}


void World::addQuad(std::vector<GLfloat> point1, std::vector<GLfloat> point2, std::vector<GLfloat> point3, std::vector<GLfloat> point4)
{
    int indexSize = vertexData.size()/3;
    
    addIndex({indexSize, indexSize +1 , indexSize +2});
    addIndex({indexSize + 3, indexSize , indexSize +2});
    
    addTriangle(point1, point2, point3);
    addVertex(point4, 1.0f, 1.0f);
}

void World::removeQuad(std::vector<GLfloat> t1v1, std::vector<GLfloat> t1v2, std::vector<GLfloat> t1v3, std::vector<GLfloat> t2v1, std::vector<GLfloat> t2v2, std::vector<GLfloat> t2v3)
{
    std::vector<GLfloat> quad = {t1v1[0], t1v1[1], t1v1[2], t1v2[0], t1v2[1], t1v2[2], t1v3[0], t1v3[1], t1v3[2], t2v1[0], t2v1[1], t2v1[2], t2v2[0], t2v2[1], t2v2[2], t2v3[0], t2v3[1], t2v3[2]};
    for (int i = 0; i < vertexData.size() - 18; i++)
    {
        std::vector<GLfloat> vertex = {vertexData[i], vertexData[i + 1], vertexData[i + 2], vertexData[i + 3], vertexData[i + 4], vertexData[i + 5], vertexData[i + 6], vertexData[i + 7], vertexData[i + 8], vertexData[i + 9], vertexData[i + 10], vertexData[i + 11], vertexData[i + 12], vertexData[i + 13], vertexData[i + 14], vertexData[i + 15], vertexData[i + 16], vertexData[i + 17]};
        if (vertex == quad)
        {
            vertexData.erase(vertexData.begin() + i, vertexData.begin() + i + 18);
            std::cout << "Quad removed" << std::endl;
            break;
        }
    }
}   


void World::addCube(std::vector<GLfloat> center, GLfloat size)
{
    // instanciate cube
    Cube cube = Cube(center, size);
    // get points
    std::vector<GLfloat> point1 = {center[0] - size/2, center[1] - size/2, center[2] - size/2};
    std::vector<GLfloat> point2 = {center[0] + size/2, center[1] - size/2, center[2] - size/2};
    std::vector<GLfloat> point3 = {center[0] + size/2, center[1] + size/2, center[2] - size/2};
    std::vector<GLfloat> point4 = {center[0] - size/2, center[1] + size/2, center[2] - size/2};
    std::vector<GLfloat> point5 = {center[0] - size/2, center[1] - size/2, center[2] + size/2};
    std::vector<GLfloat> point6 = {center[0] + size/2, center[1] - size/2, center[2] + size/2};
    std::vector<GLfloat> point7 = {center[0] + size/2, center[1] + size/2, center[2] + size/2};
    std::vector<GLfloat> point8 = {center[0] - size/2, center[1] + size/2, center[2] + size/2};

    // add quads
    addQuad(point1, point2, point3, point4);
    addQuad(point2, point6, point7, point3);
    addQuad(point6, point5, point8, point7);
    addQuad(point5, point1, point4, point8);
    addQuad(point4, point3, point7, point8);
    addQuad(point5, point6, point2, point1);

    this->chunks[0]->addCube(cube);
}

void World::addPlane(std::vector<GLfloat> center, GLfloat size, int width, int height, GLfloat noise)
{
    GLfloat currentPosX = center[0];
    GLfloat currentPosY = center[1];
    GLfloat currentPosZ = center[2];

    std::vector<std::vector<GLfloat>> points;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < width; k++)
            {
                addCube({currentPosX, currentPosY, currentPosZ}, size);
                // std::cout << "perlin noise: " << noise << std::endl;
                currentPosX += size;
            }
            currentPosZ += size;
            currentPosX = center[0];
        }
        currentPosY += size;
        currentPosZ = center[2];
        currentPosX = center[0];
    }
}


// lerp function
GLfloat World::lerp(GLfloat a, GLfloat b, GLfloat f)
{
    return a + f * (b - a);
}


// dot grid gradient
GLfloat World::dotGridGradient(int ix, int iy, GLfloat x, GLfloat y)
{
    // random gradient
    GLfloat random = 2920.0f * std::sin(ix * 21942.0f + iy * 171324.0f + 8912.0f) * std::cos(ix * 23157.0f * iy * 217832.0f + 9758.0f);
    // get gradient direction
    GLfloat xGradient = std::cos(random);
    GLfloat yGradient = std::sin(random);
    // get distance to gradient
    GLfloat xDistance = x - (GLfloat)ix;
    GLfloat yDistance = y - (GLfloat)iy;
    // dot product of distance and gradient
    return xDistance * xGradient + yDistance * yGradient;
}


GLfloat World::noise(std::vector<GLfloat> center, GLfloat size){
    // perlin noise
    int x0 = (int)center[0];
    int x1 = x0 + 1;
    int y0 = (int)center[1];
    int y1 = y0 + 1;

    // smooth the noise
    GLfloat sx = center[0] - (GLfloat)x0;
    GLfloat sy = center[1] - (GLfloat)y0;

    GLfloat n0, n1, ix0, ix1, value;
    n0 = dotGridGradient(x0, y0, center[0], center[1]);
    n1 = dotGridGradient(x1, y0, center[0], center[1]);
    ix0 = lerp(n0, n1, sx);    
    n0 = dotGridGradient(x0, y1, center[0], center[1]);
    n1 = dotGridGradient(x1, y1, center[0], center[1]);
    ix1 = lerp(n0, n1, sx);
    value = lerp(ix0, ix1, sy);

    return value;
}