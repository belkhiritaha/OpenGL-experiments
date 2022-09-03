#include "scene.hpp"

Scene::Scene()
{
    std::vector<GLfloat> black = blocks::Color(0.0f, 0.0f, 0.0f, 1.0f);
    auto colors = {black, black, black, black, black, black, black, black};
    // std::vector<std::vector<GLfloat>> colors = mat::randomColors(8);

    GLfloat blockSize = blocks::size;

    // addCube(0.0f, 0.0f, 0.0f, 0.125f, colors);

    // // colors = mat::randomColors(8);
    // addCube(0.0f, 0.0f, 0.25f, 0.125f, colors);

    // addCube(0.25f, 0.25f, 0.0f, 0.125f, colors);
    // addCube(0.25f, 0.25f, 0.25f, 0.125f, colors);

    addPlane(2, 10, 0.0f, 0.0f, 0.0f, colors);

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
    std::vector<std::vector<GLfloat>> cube = blocks::Cube(x, y, z, colors);
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
    auto plane = blocks::Plane(sizeHorz, sizeVert, x, y, z, colors);
    for (int i = 0; i < plane.size(); i++)
    {
        for (int j = 0; j < plane[i].size() - 1; j++)
        {
            vertexData.push_back(plane[i][j]);
        }
    }
    std::cout << "Plane created" << std::endl;
}