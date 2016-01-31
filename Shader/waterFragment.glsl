#version 330

in vec2 _uv;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main() {
    color = mix(texture(reflectionTexture, _uv), texture(refractionTexture, _uv), 0.5);
}