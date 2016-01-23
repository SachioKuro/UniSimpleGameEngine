#version 330

layout(location = 0) in vec3 vertexPos_ms;
layout(location = 1) in vec2 uv;

out vec2 _uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main() {
    gl_Position = PROJECTION * VIEW * MODEL * vec4(vertexPos_ms, 1);
    _uv = uv;
}