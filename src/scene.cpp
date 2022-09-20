#include "scene.hpp"

Scene::Scene()
{
    GLfloat blockSize = blocks::size;
    std::vector<GLfloat> center = {0.0f, 0.0f, 0.0f};
    // myWorld.addCube(center, blockSize);
    // myWorld.addQuad(point1, point2, point3, point4);
    myWorld.addPlane(center, blockSize, 150, 2, 0.0f);
}

Scene::~Scene()
{
    //dtor
}

void Scene::Update()
{
    myPlayer.Update();
    // std::vector<GLfloat> playerPos = myWorld.myCamera.getPlayerPosition();
    // myWorld.addPlane(playerPos, blocks::size, 2, 2, 0.0f);
}
