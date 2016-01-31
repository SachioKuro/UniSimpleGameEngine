#version 330

in vec4 _color;
in vec3 _uv;

out vec4 color;

uniform samplerCube texSampler;
uniform int FreeFlight;
uniform int UnderWater;

void main() {
	vec4 tmpcolor = texture(texSampler, _uv);
    if (UnderWater == 1 && FreeFlight == 0) {
        color = tmpcolor + vec4(-0.1,-0.2,0.1,0);
    } else {
        color = tmpcolor;
    }
}