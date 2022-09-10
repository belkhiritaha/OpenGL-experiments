#include "world.hpp"

World::World()
{
    std::cout << "World created" << std::endl;
    vertexData = {};
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

void World::addVertex(std::vector<GLfloat> vertex)
{
    vertexData.push_back(vertex[0]);
    vertexData.push_back(vertex[1]);
    vertexData.push_back(vertex[2]);
}

void World::addTriangle(std::vector<GLfloat> v1, std::vector<GLfloat> v2, std::vector<GLfloat> v3)
{
    addVertex(v1);
    addVertex(v2);
    addVertex(v3);
}

void World::addQuad(std::vector<GLfloat> t1v1, std::vector<GLfloat> t1v2, std::vector<GLfloat> t1v3, std::vector<GLfloat> t2v1, std::vector<GLfloat> t2v2, std::vector<GLfloat> t2v3)
{
    addTriangle(t1v1, t1v2, t1v3);
    addTriangle(t2v1, t2v2, t2v3);
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
    std::vector<GLfloat> p1 = {center[0] - size, center[1] - size, center[2] - size};
    std::vector<GLfloat> p2 = {center[0] + size, center[1] - size, center[2] - size};
    std::vector<GLfloat> p3 = {center[0] + size, center[1] + size, center[2] - size};
    std::vector<GLfloat> p4 = {center[0] - size, center[1] + size, center[2] - size};
    std::vector<GLfloat> p5 = {center[0] - size, center[1] - size, center[2] + size};
    std::vector<GLfloat> p6 = {center[0] + size, center[1] - size, center[2] + size};
    std::vector<GLfloat> p7 = {center[0] + size, center[1] + size, center[2] + size};
    std::vector<GLfloat> p8 = {center[0] - size, center[1] + size, center[2] + size};

    // get adjacent cubes
    std::vector<Cube> adjacentCubes;
    for (Cube cube : this->cubes)
    {
        // get norm of distance
        GLfloat norm = sqrt(pow(center[0] - cube.center[0], 2) + pow(center[1] - cube.center[1], 2) + pow(center[2] - cube.center[2], 2));
        // std::cout << "norm: " << norm <<  "size"  << size << std::endl;
        if (norm <= static_cast<GLfloat>(size * 2))
        {
            adjacentCubes.push_back(cube);
        }
    }

    // std::cout << "Adjacent cubes: " << adjacentCubes.size() << std::endl;

    std::vector<bool> drawFaces = {true, true, true, true, true, true};

    // loop through adjacent cubes
    for (Cube cube : adjacentCubes)
    {
        // get cube points
        std::vector<GLfloat> cubeP1 = {cube.center[0] - cube.size, cube.center[1] - cube.size, cube.center[2] - cube.size};
        std::vector<GLfloat> cubeP2 = {cube.center[0] + cube.size, cube.center[1] - cube.size, cube.center[2] - cube.size};
        std::vector<GLfloat> cubeP3 = {cube.center[0] + cube.size, cube.center[1] + cube.size, cube.center[2] - cube.size};
        std::vector<GLfloat> cubeP4 = {cube.center[0] - cube.size, cube.center[1] + cube.size, cube.center[2] - cube.size};
        std::vector<GLfloat> cubeP5 = {cube.center[0] - cube.size, cube.center[1] - cube.size, cube.center[2] + cube.size};
        std::vector<GLfloat> cubeP6 = {cube.center[0] + cube.size, cube.center[1] - cube.size, cube.center[2] + cube.size};
        std::vector<GLfloat> cubeP7 = {cube.center[0] + cube.size, cube.center[1] + cube.size, cube.center[2] + cube.size};
        std::vector<GLfloat> cubeP8 = {cube.center[0] - cube.size, cube.center[1] + cube.size, cube.center[2] + cube.size};
        
        // check if cube is on the right
        if (cube.center[0] < center[0])
        {
            drawFaces[0] = false;
            // remove left face
            removeQuad(cubeP1, cubeP8, cubeP5, cubeP1, cubeP8, cubeP4);
        }
        // check if cube is on the left
        if (cube.center[0] > center[0])
        {
            drawFaces[1] = false;
            // remove right face
            removeQuad(cubeP2, cubeP7, cubeP3, cubeP2, cubeP7, cubeP6);
        }

        // check if cube is on the top
        if (cube.center[1] < center[1])
        {
            drawFaces[2] = false;
            // remove bottom face
            removeQuad(cubeP4, cubeP7, cubeP8, cubeP4, cubeP7, cubeP3);
        }
        // check if cube is on the bottom
        if (cube.center[1] > center[1])
        {
            drawFaces[3] = false;
            // remove top face
            removeQuad(cubeP1, cubeP6, cubeP2, cubeP1, cubeP6, cubeP5);
        }

        // this block is good
        // check if cube is in front
        if (cube.center[2] > center[2])
        {
            drawFaces[4] = false;
            // remove back face
            removeQuad(cubeP4, cubeP2, cubeP3, cubeP4, cubeP1, cubeP2);
        }
        // check if cube is behind
        if (cube.center[2] < center[2])
        {
            drawFaces[5] = false;
            // remove front face
            removeQuad(cubeP5, cubeP8, cubeP6, cubeP8, cubeP7, cubeP6);
        }
        
    }
    // draw front face
    if (drawFaces[0])
    {
        addQuad(p5, p8, p6, p8, p7, p6);
    }
    // draw back face
    if (drawFaces[1])
    {
        addQuad(p4, p2, p3, p4, p1, p2);
    }
    // draw top face
    if (drawFaces[2])
    {
        addQuad(p1, p6, p2, p1, p6, p5);
    }
    // draw bottom face
    if (drawFaces[3])
    {
        addQuad(p4, p7, p8, p4, p7, p3);
    }
    // draw right face
    if (drawFaces[4])
    {
        addQuad(p2, p7, p3, p2, p7, p6);
    }
    // draw left face
    if (drawFaces[5])
    {
        addQuad(p1, p8, p5, p1, p8, p4);
    }

    // addQuad(p5, p8, p6, p8, p7, p6);
    // addQuad(p4, p2, p3, p4, p1, p2);
    // addQuad(p1, p6, p2, p1, p6, p5);
    // addQuad(p4, p7, p8, p4, p7, p3);
    // addQuad(p2, p7, p3, p2, p7, p6);
    // addQuad(p1, p8, p5, p1, p8, p4);

    cubes.push_back(Cube(center, size));
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
                currentPosX += size * 2;
            }
            currentPosZ += size * 2;
            currentPosX = center[0];
        }
        currentPosY += size * 2;
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