#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>
#include <glad/glad.h>



class Cube {
    public:
        Cube(std::vector<GLfloat> center, GLfloat size);
        ~Cube();
        int id;
        GLfloat size;
        std::vector<GLfloat> center;
};