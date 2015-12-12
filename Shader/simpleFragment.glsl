#version 330

//in vec2 UV

out vec3 color;

uniform sampler2D texSampler;

void main() {
	//color = texture(texSampler, UV).rgb;
	color = vec3(1.0, 1.0, 0.2);
}