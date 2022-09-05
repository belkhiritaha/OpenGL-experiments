#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <iostream>
#include "mat.hpp"


namespace blocks {
    // typedef std::vector<std::vector<GLfloat>> to pointsList
    typedef std::vector<GLfloat> point;
    typedef std::vector<point> pointsList;
    typedef std::vector<GLfloat> color;
    typedef std::vector<color> colorsList;

    const GLfloat size = 0.25f;

    colorsList randomColors(int n);

    color Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    point Point(GLfloat x, GLfloat y, GLfloat z, std::vector<GLfloat> color);

    pointsList Cube(GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors, std::vector<GLfloat> &vertexData);

    pointsList Plane(GLint sizeHorz, GLint sizeVert ,GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors, std::vector<GLfloat> &vertexData);

    std::vector<GLfloat> RemoveAdjacentVertices(pointsList points, std::vector<GLfloat> vertexData);

    blocks::point CenterPoint(blocks::pointsList face);
};