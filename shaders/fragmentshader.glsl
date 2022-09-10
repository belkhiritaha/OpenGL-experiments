#version 410 core

uniform float time;
in vec3 v_vertexColors;

out vec4 color;

void main()
{
    // color = vec4(v_vertexColors.r , v_vertexColors.g, v_vertexColors.b , 1);
    color = vec4(0.0, 0.0, 0.0, 1.0);
}