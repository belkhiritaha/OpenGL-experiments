#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <glad/glad.h>
#include "blocks.hpp"

#define PI 3.14159265359
#define RED mat::Color(1.0f, 0.0f, 0.0f, 1.0f)


namespace mat {

    std::vector<std::vector<GLfloat>> randomColors(int n);

    std::vector<GLfloat> Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    std::vector<GLfloat> Point(GLfloat x, GLfloat y, GLfloat z, std::vector<GLfloat> color);

    std::vector<std::vector<GLfloat>> Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, std::vector<std::vector<GLfloat>> colors);


    glm::mat4 translationMatrix(float x, float y, float z);

    glm::mat4 rotationMatrix(float theta, float phi, float alpha);

    glm::mat4 projectionMatrix(float fov, float aspect, float near, float far);

    glm::mat4 viewMatrix(float x, float y, float z, float theta, float phi, float alpha);

    glm::mat4 modelMatrix(float x, float y, float z, float theta, float phi, float alpha);
};