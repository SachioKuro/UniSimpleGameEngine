#version 330

layout(location = 0) in vec3 vertexPos_ms;

out vec3 blendC;

uniform mat4 MVP;
uniform vec3 BlendColor = vec3(1.0f,1.0f,1.0f);

void main() {
	gl_Position = MVP * vec4(vertexPos_ms, 1);
	blendC = BlendColor;
}