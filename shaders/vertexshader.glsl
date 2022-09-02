#version 410 core

uniform float time;
uniform mat4 transform;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColors;

out vec3 v_vertexColors;

void main()
{

    // rotate point
    vec4 p = vec4(position, 1.0);

    p = p * transform;


    v_vertexColors = vertexColors;
    gl_Position = p;

    //gl_Position = vec4(position, 1.0);
}