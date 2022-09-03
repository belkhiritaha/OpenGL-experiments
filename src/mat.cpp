#include "mat.hpp"



std::vector<GLfloat> mat::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    return std::vector<GLfloat>{r, g, b, a};
};

std::vector<std::vector<GLfloat>> mat::randomColors(int n) {
    std::vector<std::vector<GLfloat>> colors;
    for (int i = 0; i < n; i++) {
        colors.push_back(mat::Color((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f));
        // colors.push_back(mat::Color(1.0f, 0.0f, 0.0f, 1.0f));
    }
    return colors;
};

std::vector<GLfloat> mat::Point(GLfloat x, GLfloat y, GLfloat z, std::vector<GLfloat> color) {
    return std::vector<GLfloat>{x, y, z, color[0], color[1], color[2], color[3]};
};


std::vector<std::vector<GLfloat>> mat::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size, std::vector<std::vector<GLfloat>> colors) {
    std::vector<std::vector<GLfloat>> points;
    auto p0 = mat::Point(x - size, y - size, z - size, colors[0]);
    auto p1 = mat::Point(x + size, y - size, z - size, colors[1]);
    auto p2 = mat::Point(x + size, y + size, z - size, colors[2]);
    auto p3 = mat::Point(x - size, y + size, z - size, colors[3]);
    auto p4 = mat::Point(x - size, y - size, z + size, colors[4]);
    auto p5 = mat::Point(x + size, y - size, z + size, colors[5]);
    auto p6 = mat::Point(x + size, y + size, z + size, colors[6]);
    auto p7 = mat::Point(x - size, y + size, z + size, colors[7]);
    
    // Back face
    points.push_back(p0);
    points.push_back(p2);
    points.push_back(p1);

    points.push_back(p0);
    points.push_back(p3);
    points.push_back(p2);

    // Left face
    points.push_back(p0);
    points.push_back(p3);
    points.push_back(p4);

    points.push_back(p3);
    points.push_back(p7);
    points.push_back(p4);

    // Right face
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p5);

    points.push_back(p2);
    points.push_back(p6);
    points.push_back(p5);

    // Bottom face
    points.push_back(p3);
    points.push_back(p7);
    points.push_back(p2);

    points.push_back(p7);
    points.push_back(p6);
    points.push_back(p2);

    // Top face
    points.push_back(p0);
    points.push_back(p4);
    points.push_back(p1);

    points.push_back(p1);
    points.push_back(p4);
    points.push_back(p5);

    // Front face
    points.push_back(p4);
    points.push_back(p7);
    points.push_back(p5);

    points.push_back(p7);
    points.push_back(p6);
    points.push_back(p5);

    return points;
};


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


