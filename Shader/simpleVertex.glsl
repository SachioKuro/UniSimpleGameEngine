#version 330

layout(location = 0) in vec3 vertexPos_ms;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 color;

out vec4 _color;
out vec2 _uv;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPos_ms, 1);
    _color = color;
    _uv = uv;
}