#version 150

in vec3 position;
in vec3 normal;
in vec3 color;
in vec2 uv;

out vec3 Color;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = color;
	Normal = normal;
	TexCoord = uv;
    gl_Position = projection * view * model * vec4( position, 1.0 );
}