#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.14159265359
#define RED mat::Color(1.0f, 0.0f, 0.0f, 1.0f)


namespace mat {

    struct Color {
        float r;
        float g;
        float b;
        float a;
    };

    struct Point {
        float x;
        float y;
        float z;
    };


    glm::mat4 translationMatrix(float x, float y, float z);

    glm::mat4 rotationMatrix(float theta, float phi, float alpha);

    glm::mat4 projectionMatrix(float fov, float aspect, float near, float far);

    glm::mat4 viewMatrix(float x, float y, float z, float theta, float phi, float alpha);

    glm::mat4 modelMatrix(float x, float y, float z, float theta, float phi, float alpha);
};