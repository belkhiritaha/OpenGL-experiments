#include "blocks.hpp"

std::vector<GLfloat> blocks::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    return std::vector<GLfloat>{r, g, b, a};
};

std::vector<std::vector<GLfloat>> blocks::randomColors(int n) {
    std::vector<std::vector<GLfloat>> colors;
    for (int i = 0; i < n; i++) {
        colors.push_back(blocks::Color((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 1.0f));
        // colors.push_back(mat::Color(1.0f, 0.0f, 0.0f, 1.0f));
    }
    return colors;
};

std::vector<GLfloat> blocks::Point(GLfloat x, GLfloat y, GLfloat z, std::vector<GLfloat> color) {
    return std::vector<GLfloat>{x, y, z, color[0], color[1], color[2], color[3]};
};


std::vector<std::vector<GLfloat>> blocks::Cube(GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors) {
    std::vector<std::vector<GLfloat>> points;
    auto p0 = blocks::Point(x - size, y - size, z - size, colors[0]);
    auto p1 = blocks::Point(x + size, y - size, z - size, colors[1]);
    auto p2 = blocks::Point(x + size, y + size, z - size, colors[2]);
    auto p3 = blocks::Point(x - size, y + size, z - size, colors[3]);
    auto p4 = blocks::Point(x - size, y - size, z + size, colors[4]);
    auto p5 = blocks::Point(x + size, y - size, z + size, colors[5]);
    auto p6 = blocks::Point(x + size, y + size, z + size, colors[6]);
    auto p7 = blocks::Point(x - size, y + size, z + size, colors[7]);
    
    // Back face
    points.push_back(p0); points.push_back(p2); points.push_back(p1);

    points.push_back(p0); points.push_back(p3); points.push_back(p2);

    // Left face
    points.push_back(p0); points.push_back(p3); points.push_back(p4);

    points.push_back(p3); points.push_back(p7); points.push_back(p4);

    // Right face
    points.push_back(p1); points.push_back(p2); points.push_back(p5); 
    
    points.push_back(p2); points.push_back(p6); points.push_back(p5);

    // Bottom face
    points.push_back(p3); points.push_back(p7); points.push_back(p2);
    
    points.push_back(p7); points.push_back(p6); points.push_back(p2);

    // Top face
    points.push_back(p0); points.push_back(p4); points.push_back(p1);
    
    points.push_back(p1); points.push_back(p4); points.push_back(p5);

    // Front face
    points.push_back(p4); points.push_back(p7); points.push_back(p5);
    
    points.push_back(p7); points.push_back(p6); points.push_back(p5);

    return points;
};


blocks::pointsList blocks::Plane(GLint sizeHorz, GLint sizeVert ,GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors){
    GLfloat currentPosX = x;
    GLfloat currentPosY = y;
    GLfloat currentPosZ = z;

    std::vector<std::vector<GLfloat>> points;
    for (int i = 0; i < sizeHorz; i++) {
        for (int j = 0; j < sizeVert; j++) {
            for (int k = 0; k < sizeVert; k++) {
                auto cube = blocks::Cube(currentPosX, currentPosY, currentPosZ, colors);
                points.insert(points.end(), cube.begin(), cube.end());
                currentPosX += size * 2;
            }
            currentPosZ += size * 2;
            currentPosX = x;
        }
        currentPosY += size * 2;
        currentPosZ = z;
        currentPosX = x;
    }
    return points;
}