#version 330

in vec4 _color;
in vec2 _uv;

out vec4 out_color;

uniform vec4 blendColor;
uniform sampler2D texSampler;

void main() { 
    //if (color.a > 0.5)
    //    discard;
    out_color = texture(texSampler, _uv) + blendColor;
}