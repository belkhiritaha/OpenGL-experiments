#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Camera{
    public:
        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

        // float aspectRatio = 16/9;
        float aspectRatio = 1.0f;

        float speed = 0.1f;
        float sensitivity = 0.1f;

        int Keys[4];

        Camera();
        glm::mat4 Matrix(float FOVDegrees, float nearPlane, float farPlane);
        void Input();  

        std::vector<GLfloat> getPlayerPosition();
        std::vector<int> getPlayerChunk();
};