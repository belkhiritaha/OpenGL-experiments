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
    return glm::mat4(1.0f / (aspect * tan(fov / 2.0f)), 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f / tan(fov / 2.0f), 0.0f, 0.0f,
                        0.0f, 0.0f, (near + far) / (near - far), (2.0f * near * far) / (near - far),
                        0.0f, 0.0f, -1.0f, 0.0f);
}

glm::mat4 mat::viewMatrix(float x, float y, float z, float theta, float phi, float alpha) {
    return glm::mat4(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta), 0.0f,
                        sin(alpha) * sin(theta) * cos(phi) - cos(alpha) * sin(phi), sin(alpha) * sin(theta) * sin(phi) + cos(alpha) * cos(phi), sin(alpha) * cos(theta), 0.0f,
                        cos(alpha) * sin(theta) * cos(phi) + sin(alpha) * sin(phi), cos(alpha) * sin(theta) * sin(phi) - sin(alpha) * cos(phi), cos(alpha) * cos(theta), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f) * glm::mat4(1.0f, 0.0f, 0.0f, -x,
                                                            0.0f, 1.0f, 0.0f, -y,
                                                            0.0f, 0.0f, 1.0f, -z,
                                                            0.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat4 mat::modelMatrix(float x, float y, float z, float theta, float phi, float alpha) {
    return glm::mat4(cos(theta) * cos(phi), cos(theta) * sin(phi), -sin(theta), 0.0f,
                        sin(alpha) * sin(theta) * cos(phi) - cos(alpha) * sin(phi), sin(alpha) * sin(theta) * sin(phi) + cos(alpha) * cos(phi), sin(alpha) * cos(theta), 0.0f,
                        cos(alpha) * sin(theta) * cos(phi) + sin(alpha) * sin(phi), cos(alpha) * sin(theta) * sin(phi) - sin(alpha) * cos(phi), cos(alpha) * cos(theta), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f) * glm::mat4(1.0f, 0.0f, 0.0f, x,
                                                            0.0f, 1.0f, 0.0f, y,
                                                            0.0f, 0.0f, 1.0f, z,
                                                            0.0f, 0.0f, 0.0f, 1.0f);
}


