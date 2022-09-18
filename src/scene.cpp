#include "scene.hpp"

Scene::Scene()
{
    GLfloat blockSize = blocks::size;
    std::vector<GLfloat> center = {0.0f, 0.0f, 0.0f};
    myWorld.addCube(center, blockSize);
    // myWorld.addQuad(point1, point2, point3, point4);
}

Scene::~Scene()
{
    //dtor
}

void Scene::Update()
{
    myPlayer.Update();
}


void Scene::addCube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, std::vector<std::vector<GLfloat>> colors)
{
    std::vector<std::vector<GLfloat>> cube = blocks::Cube(x, y, z, colors, vertexData);
    for (int i = 0; i < cube.size(); i++)
    {
        for (int j = 0; j < cube[i].size() - 1; j++)
        {
            vertexData.push_back(cube[i][j]);
        }
    }
    std::cout << "Cube created" << std::endl;
}


void Scene::addPlane(GLint sizeHorz, GLint sizeVert, GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors)
{
    auto plane = blocks::Plane(sizeHorz, sizeVert, x, y, z, colors, vertexData);
    // auto newVertexData = blocks::RemoveAdjacentVertices(plane, vertexData);
    // vertexData = newVertexData;

    for (int i = 0; i < plane.size(); i++)
    {
        for (int j = 0; j < plane[i].size() - 1; j++)
        {
            vertexData.push_back(plane[i][j]);
        }
    }

    std::cout << "Plane created" << std::endl;
}