#include "scene.hpp"

Scene::Scene()
{
    std::vector<GLfloat> black = blocks::Color(0.0f, 0.0f, 0.0f, 1.0f);
    auto colors = {black, black, black, black, black, black, black, black};
    // std::vector<std::vector<GLfloat>> colors = mat::randomColors(8);

    GLfloat blockSize = 0.5f;

    addCube(0.0f, 0.0f, 0.0f, 0.125f, colors);

    // colors = mat::randomColors(8);
    addCube(0.0f, 0.0f, 0.25f, 0.125f, colors);

    addCube(0.25f, 0.25f, 0.0f, 0.125f, colors);
    addCube(0.25f, 0.25f, 0.25f, 0.125f, colors);

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

    // Add indices
    // set index as max of indexBufferData + 1 or 0 if indexBufferData is empty
    GLuint index = indexBufferData.empty() ? 0 : *std::max_element(indexBufferData.begin(), indexBufferData.end()) + 1;
    std::vector<GLuint> indices = {
        index, index + 1, index + 2,
        index + 2, index + 3, index,

        index + 3, index + 7, index + 2,
        index + 7, index + 6, index + 2,

        index + 4, index + 5, index + 1,
        index + 4, index + 1, index + 0,

        index + 7, index + 3 , index + 0,
        index + 7, index + 0, index + 4,

        index + 5, index + 6, index + 2,
        index + 5, index + 2, index + 1,

        index + 7, index + 6, index + 5,
        index + 7, index + 5, index + 4
    };
    for (int i = 0; i < indices.size(); i++)
    {
        indexBufferData.push_back(indices[i]);
    }
    // Add vertices
    std::vector<std::vector<GLfloat>> cube = blocks::Cube(x, y, z, size, colors);
    for (int i = 0; i < cube.size(); i++)
    {
        for (int j = 0; j < cube[i].size() - 1; j++)
        {
            vertexData.push_back(cube[i][j]);
        }
    }
    std::cout << "Cube created" << std::endl;
}
