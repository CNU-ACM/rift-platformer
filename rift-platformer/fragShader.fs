#version 150

in vec4 fragColor;
in vec2 fragTexCoords;

uniform sampler2D sampler0;
out vec4 color;

void main()
{
    color = texture(sampler0, fragTexCoords);
}

