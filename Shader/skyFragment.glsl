#version 330

in vec4 _color;
in vec3 _uv;

out vec4 color;

uniform samplerCube texSampler;

void main() {
	color = texture(texSampler, _uv);
}