#version 330

in vec4 _color;
in vec2 _uv;

out vec4 color;

uniform int renderType; 
uniform sampler2D texSampler;

void main() {
	switch(renderType) {
        case 0:
            color = texture(texSampler, _uv) + _color;
            break;
        case 1:
            color = _color;
            break;
        default:
            color = vec4(0, 0, 0, 1);     
     }   
}