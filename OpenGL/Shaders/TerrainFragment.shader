#version 150

in vec3 Color;
in vec3 Normal;
in vec2 TexCoord;

out vec4 outColor;

const vec3 dir = normalize(vec3(-1.0, -1.0, -1.0));
const vec3 ambi = vec3(0.2, 0.2, 0.2);

uniform sampler2D tex;

void main()
{
	vec3 col = texture(tex, TexCoord).xyz;
    outColor = vec4(min(col * dot(Normal, dir) + ambi, 1.0), 1.0 );
}