#include "camera.hpp"
#include "blocks.hpp"

Camera::Camera()
{
    
}


glm::mat4 Camera::Matrix(float FOVDegrees, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVDegrees), aspectRatio, nearPlane, farPlane);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model;
    return mvp;
}


void Camera::Input(){
    if(Keys[0] == 1){
        Position += speed * Orientation;
    }
    if(Keys[1] == 1){
        Position -= speed * Orientation;
    }
    if(Keys[2] == 1){
        Position -= speed * glm::cross(Orientation, Up);
    }
    if(Keys[3] == 1){
        Position += speed * glm::cross(Orientation, Up);
    }
}


std::vector<GLfloat> Camera::getPlayerPosition(){
    std::vector<GLfloat> playerPos = {0, 0, 0};
    playerPos[0] = Position[0];
    playerPos[1] = Position[1];
    playerPos[2] = Position[2];
    return playerPos;
}


std::vector<int> Camera::getPlayerChunk()
{
    int posX = Position[0]/blocks::size;
    int posY = Position[2]/blocks::size;

    std::vector<int> chunkPos = {posX, posY};
    return chunkPos;
}