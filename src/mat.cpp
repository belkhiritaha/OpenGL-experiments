#include "mat.hpp"

glm::mat4 mat::translationMatrix(float x, float y, float z) {
    return glm::mat4(1.0f, 0.0f, 0.0f, x,
                        0.0f, 1.0f, 0.0f, y,
                        0.0f, 0.0f, 1.0f, z,
                        0.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat4 mat::rotationMatrix(float theta, float phi, float alpha) {
    return glm::mat4(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta), 0.0f,
                        sin(alpha) * sin(theta) * cos(phi) - cos(alpha) * sin(phi), sin(alpha) * sin(theta) * sin(phi) + cos(alpha) * cos(phi), sin(alpha) * cos(theta), 0.0f,
                        cos(alpha) * sin(theta) * cos(phi) + sin(alpha) * sin(phi), cos(alpha) * sin(theta) * sin(phi) - sin(alpha) * cos(phi), cos(alpha) * cos(theta), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat4 mat::projectionMatrix(float fov, float aspect, float near, float far) {
    return glm::perspective(glm::radians(90.0f), aspect, 0.1f, 1000.0f);
}

glm::mat4 mat::viewMatrix(float x, float y, float z, float theta, float phi, float alpha) {
    //return glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * mat::rotationMatrix(theta, phi, alpha);
    glm::vec3 camPos = glm::vec3(x, y, z);
    glm::vec3 camFront = glm::vec3(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta));
    // glm::vec3 camUp = glm::vec3(sin(alpha) * sin(theta) * cos(phi) - cos(alpha) * sin(phi), sin(alpha) * sin(theta) * sin(phi) + cos(alpha) * cos(phi), sin(alpha) * cos(theta));
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);
    return glm::lookAt(camPos, camPos + camFront, camUp);
    // return glm::lookAt(glm::vec3(x, y, z), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 mat::modelMatrix(float x, float y, float z, float theta, float phi, float alpha) {
    return glm::mat4(1.0f);
}


