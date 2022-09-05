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


std::vector<std::vector<GLfloat>> blocks::Cube(GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors, std::vector<GLfloat> &vertexData) {
    std::vector<std::vector<GLfloat>> points;
    auto p0 = blocks::Point(x - size, y - size, z - size, colors[0]);
    auto p1 = blocks::Point(x + size, y - size, z - size, colors[1]);
    auto p2 = blocks::Point(x + size, y + size, z - size, colors[2]);
    auto p3 = blocks::Point(x - size, y + size, z - size, colors[3]);
    auto p4 = blocks::Point(x - size, y - size, z + size, colors[4]);
    auto p5 = blocks::Point(x + size, y - size, z + size, colors[5]);
    auto p6 = blocks::Point(x + size, y + size, z + size, colors[6]);
    auto p7 = blocks::Point(x - size, y + size, z + size, colors[7]);
    
    // Get verticesPoints from vertex data
    blocks::pointsList verticesPoints;
    for (int i = 0; i < vertexData.size(); i += 7) {
        verticesPoints.push_back(std::vector<GLfloat>{vertexData[i], vertexData[i + 1], vertexData[i + 2], vertexData[i + 3], vertexData[i + 4], vertexData[i + 5], vertexData[i + 6]});
    }

    // Group verticesPoints by faces
    std::vector<blocks::pointsList> faces;
    for (int i = 0; i < verticesPoints.size(); i+=4) {
        faces.push_back(blocks::pointsList{verticesPoints[i], verticesPoints[i + 1], verticesPoints[i + 2], verticesPoints[i + 3]});
    }

    // Get center points of faces
    blocks::pointsList centerPoints;
    for (auto face : faces) {
        centerPoints.push_back(blocks::CenterPoint(face));
    }

    // Back face
    blocks::pointsList backFace;
    backFace.push_back(p0);
    backFace.push_back(p1);
    backFace.push_back(p2);
    backFace.push_back(p3);
    std::vector<GLfloat> backFaceCenterPoint = blocks::CenterPoint(backFace);
    // if backFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), backFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p0); points.push_back(p2); points.push_back(p1);
        points.push_back(p0); points.push_back(p3); points.push_back(p2);
    }

    // Left face
    blocks::pointsList leftFace;
    leftFace.push_back(p0);
    leftFace.push_back(p4);
    leftFace.push_back(p7);
    leftFace.push_back(p3);
    std::vector<GLfloat> leftFaceCenterPoint = blocks::CenterPoint(leftFace);
    // if leftFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), leftFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p0); points.push_back(p3); points.push_back(p4);
        points.push_back(p3); points.push_back(p7); points.push_back(p4);
    }

    // Right face
    blocks::pointsList rightFace;
    rightFace.push_back(p1);
    rightFace.push_back(p5);
    rightFace.push_back(p6);
    rightFace.push_back(p2);
    std::vector<GLfloat> rightFaceCenterPoint = blocks::CenterPoint(rightFace);
    // if rightFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), rightFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p2); points.push_back(p6); points.push_back(p5);
        points.push_back(p1); points.push_back(p2); points.push_back(p5); 
    }

    // Bottom face
    blocks::pointsList bottomFace;
    bottomFace.push_back(p0);
    bottomFace.push_back(p1);
    bottomFace.push_back(p5);
    bottomFace.push_back(p4);
    std::vector<GLfloat> bottomFaceCenterPoint = blocks::CenterPoint(bottomFace);
    // if bottomFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), bottomFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p3); points.push_back(p7); points.push_back(p2);
        points.push_back(p7); points.push_back(p6); points.push_back(p2);
    }

    // Top face
    blocks::pointsList topFace;
    topFace.push_back(p4);
    topFace.push_back(p5);
    topFace.push_back(p6);
    topFace.push_back(p7);
    std::vector<GLfloat> topFaceCenterPoint = blocks::CenterPoint(topFace);
    // if topFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), topFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p1); points.push_back(p4); points.push_back(p5);
        points.push_back(p0); points.push_back(p4); points.push_back(p1);
    }

    // Front face
    blocks::pointsList frontFace;
    frontFace.push_back(p4);
    frontFace.push_back(p5);
    frontFace.push_back(p6);
    frontFace.push_back(p7);
    std::vector<GLfloat> frontFaceCenterPoint = blocks::CenterPoint(frontFace);
    // if frontFace is not in faces
    if (std::find(centerPoints.begin(), centerPoints.end(), frontFaceCenterPoint) == centerPoints.end()) {
        points.push_back(p4); points.push_back(p7); points.push_back(p5);
        points.push_back(p7); points.push_back(p6); points.push_back(p5);
    }

    std::cout << "vertexData.size(): " << vertexData.size() << std::endl;

    for (int i = 0; i < points.size(); i++)
    {
        for (int j = 0; j < points[i].size() - 1; j++)
        {
            vertexData.push_back(points[i][j]);
        }
    }
 
    std::cout << "vertexData.size(): " << vertexData.size() << std::endl;
    return points;
};


blocks::pointsList blocks::Plane(GLint sizeHorz, GLint sizeVert ,GLfloat x, GLfloat y, GLfloat z, std::vector<std::vector<GLfloat>> colors, std::vector<GLfloat> &vertexData) {
    GLfloat currentPosX = x;
    GLfloat currentPosY = y;
    GLfloat currentPosZ = z;

    auto tmpVertexData = vertexData;

    std::vector<std::vector<GLfloat>> points;
    for (int i = 0; i < sizeHorz; i++) {
        for (int j = 0; j < sizeVert; j++) {
            for (int k = 0; k < sizeVert; k++) {
                std::cout << "i: " << i << " j: " << j << " k: " << k << std::endl;
                auto cube = blocks::Cube(currentPosX, currentPosY, currentPosZ, colors, tmpVertexData);
                std::cout << "block created" << std::endl;
                //points.insert(points.end(), cube.begin(), cube.end());
                currentPosX += size * 2;
            }
            currentPosZ += size * 2;
            currentPosX = x;
        }
        currentPosY += size * 2;
        currentPosZ = z;
        currentPosX = x;
    }
    vertexData = tmpVertexData;
    return points;
}


std::vector<GLfloat> blocks::RemoveAdjacentVertices(pointsList points, std::vector<GLfloat> vertexData){
    std::vector<GLfloat> newVertexData;
    // get points coordinates
    std::vector<GLfloat> pointsCoordinates;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < 3; j++) {
            pointsCoordinates.push_back(points[i][j]);
        }
    }

    // get color values
    std::vector<GLfloat> pointsColors;
    for (int i = 0; i < points.size(); i++) {
        for (int j = 3; j < 7; j++) {
            pointsColors.push_back(points[i][j]);
        }
    }

    // remove adjacent vertices
    for (int i = 0; i < vertexData.size(); i += 7) {
        std::vector<GLfloat> vertex;
        for (int j = 0; j < 3; j++) {
            vertex.push_back(vertexData[i + j]);
        }
        if (std::find(pointsCoordinates.begin(), pointsCoordinates.end(), vertex[0]) != pointsCoordinates.end() &&
            std::find(pointsCoordinates.begin(), pointsCoordinates.end(), vertex[1]) != pointsCoordinates.end() &&
            std::find(pointsCoordinates.begin(), pointsCoordinates.end(), vertex[2]) != pointsCoordinates.end()) {
            for (int j = 0; j < 7; j++) {
                newVertexData.push_back(vertexData[i + j]);
            }
        }
    }



    return newVertexData;
}

blocks::point blocks::CenterPoint(blocks::pointsList face){
    std::vector<GLfloat> centerPoint = {0.0f, 0.0f, 0.0f};
    for (int i = 0; i < face.size(); i++){
        centerPoint[0] += face[i][0];
        centerPoint[1] += face[i][1];
        centerPoint[2] += face[i][2];
    }
    centerPoint[0] /= face.size();
    centerPoint[1] /= face.size();
    centerPoint[2] /= face.size();
    return centerPoint;
}