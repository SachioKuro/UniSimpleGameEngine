#version 330

in vec2 _uv;
smooth in vec3 _pos_ws;
smooth in vec3 _normal_cs;
smooth in vec3 _eye_cs;
smooth in vec3 _light_cs;

out vec4 color;

uniform sampler2D texSampler;
uniform vec3 lightPosition;
uniform int FreeFlight;
uniform int UnderWater;

void main() {
    vec3 lightColor = vec3(0.75,0.75,0.7);
    
    vec3 normal = normalize(_normal_cs);
    vec3 lightDirection = normalize(_light_cs - _pos_ws);
    float cosTheta = clamp(dot(normal , lightDirection), 0.0,1.0 );
    
    vec4 texel = texture(texSampler, _uv);
    vec4 tmp_color = vec4(texel.rgb * vec3(0.3, 0.3, 0.3), texel.a) + 
                     vec4(texel.rgb * lightColor * cosTheta, texel.a);

    if (FreeFlight == 0) {       
        if (UnderWater == 1)
            tmp_color = tmp_color + vec4(-0.1,-0.2,0.1,0);
        vec4 fog_color = vec4(0.7f, 0.7f, 0.8f, 1.0f);
        color = mix(tmp_color, fog_color, 1.0 - clamp(1.0/exp(pow(length(_eye_cs)*0.014,2)), 0.0, 1.0));
    } else {
        color = tmp_color;
    }
}