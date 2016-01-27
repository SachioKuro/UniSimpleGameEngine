#version 330

layout(location = 0) in vec3 vertexPos_ms;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal_ms;

out vec2 _uv;
out vec3 _pos_ws;
out vec3 _normal_cs;
out vec3 _eye_cs;
out vec3 _light_cs;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;
uniform vec3 lightPosition;
uniform vec4 clippingPlane;

void main() {
    gl_ClipDistance[0] = dot(vec4(vertexPos_ms, 1), clippingPlane);
    gl_Position = PROJECTION * VIEW * MODEL * vec4(vertexPos_ms, 1);
    _pos_ws = (MODEL * vec4(vertexPos_ms, 1)).xyz;
    _eye_cs = vec3(0, 0, 0) - (VIEW * MODEL * vec4(vertexPos_ms, 1)).xyz;
    _light_cs = (VIEW * vec4(lightPosition, 1)).xyz + _eye_cs;
    _normal_cs = normal_ms;
    _uv = uv;
    
}