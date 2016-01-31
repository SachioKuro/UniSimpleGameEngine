#version 330

in vec2 _uv;
smooth in vec3 _eye_cs;

out vec4 color;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform int FreeFlight;

void main() {
    vec4 tmp_color = mix(texture(reflectionTexture, _uv), texture(refractionTexture, _uv), 0.5);
    if (FreeFlight == 0) {      
        vec4 fog_color = vec4(0.7f, 0.7f, 0.8f, 1.0f);
        color = mix(tmp_color, fog_color, 1.0 - clamp(1.0/exp(pow(length(_eye_cs)*0.014,2)), 0.0, 1.0));
    } else {
        color = tmp_color;
    }
}