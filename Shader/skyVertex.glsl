#version 430

layout(location = 0) in vec3 vertexPos_ms;
layout(location = 1) in vec2 vertex_uv;
out vec2 uv;
out vec3 blendC;

uniform mat4 MVP;
uniform vec3 BlendColor = vec3(1.0f,1.0f,1.0f);

void main() {
	gl_Position = MVP * vec4(vertexPos_ms, 1);
	blendC = BlendColor;
	uv = vertex_uv;
}