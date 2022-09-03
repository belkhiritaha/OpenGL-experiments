#include "scene.hpp"

Scene::Scene()
{
    std::vector<GLfloat> color = mat::Color(1.0f, 0.0f, 0.0f, 1.0f);
    std::vector<std::vector<GLfloat>> colors = mat::randomColors(8);
    std::cout << "Scene created" << std::endl;
    addCube(0.0f, 0.0f, 0.0f, 0.25f, colors);

    colors = mat::randomColors(8);
    addCube(0.5f, 0.5f, 0.5f, 0.25f, colors);

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
    std::cout << "index: " << index << std::endl;
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
    std::cout << "indexBufferData size: " << indexBufferData.size() << std::endl;
    // print indexBufferData
    for (int i = 0; i < indexBufferData.size(); i++)
    {
        std::cout << indexBufferData[i] << " ";
    }

    // Add vertices
    std::vector<std::vector<GLfloat>> cube = mat::Cube(x, y, z, size, colors);
    std::cout << "cube size: " << cube.size() << std::endl;
    std::cout << "vertexData size: " << vertexData.size() << std::endl;
    for (int i = 0; i < cube.size(); i++)
    {
        for (int j = 0; j < cube[i].size() - 1; j++)
        {
            vertexData.push_back(cube[i][j]);
        }
    }
    std::cout << "Cube created" << std::endl;
}
