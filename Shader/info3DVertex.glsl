#version 330

layout(location = 0) in vec3 vertexPos_ms;
layout(location = 3) in vec4 color;

out vec4 _color;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPos_ms, 1);
    _color = color;
}