#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>



namespace blocks {

    std::vector<std::vector<GLfloat>> randomColors(int n);

    std::vector<GLfloat> Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    std::vector<GLfloat> Point(GLfloat x, GLfloat y, GLfloat z, std::vector<GLfloat> color);

    std::vector<std::vector<GLfloat>> Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, std::vector<std::vector<GLfloat>> colors);

};