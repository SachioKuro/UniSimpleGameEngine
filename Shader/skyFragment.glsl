#version 430

in vec2 uv;
in vec3 blendC;

out vec3 color;

uniform sampler2D texSampler;

void main() {
	//color = texture(texSampler, UV).rgb;
	color = texture(texSampler, uv).rgb;
	//color = vec4(tex, 1.0);
}