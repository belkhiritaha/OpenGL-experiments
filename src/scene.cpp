#include "scene.hpp"

Scene::Scene()
{
    blocks::color black = blocks::Color(0.0f, 0.0f, 0.0f, 1.0f);
    auto colors = {black, black, black, black, black, black, black, black};
    //std::vector<std::vector<GLfloat>> colors = blocks::randomColors(8);

    GLfloat blockSize = blocks::size;

    //auto newVertices = blocks::createVertices(blockSize);

    // addPlane(2, 100, 0.0f, 0.0f, 0.0f, colors, );
    // auto plane = blocks::Plane(2, 100, 0.0f, 0.0f, 0.0f, colors, Scene::vertexData);

    std::vector<GLfloat> center = {0.0f, 0.0f, 0.0f};
    //myWorld.addCube(center, blockSize);

    myWorld.addPlane(center, blockSize, 20, 1, myWorld.noise({1.0f, 3.0f, 2.5f}, blockSize));

    std::cout << "vertices:" << myWorld.vertexData.size() << std::endl;

    center = {0.0f, 2 * blockSize, 0.0f};
    myWorld.addCube(center, blockSize);

    // print vertices
    std::cout << "vertices:" << myWorld.vertexData.size() << std::endl;

    std::cout << "Scene created" << std::endl;
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