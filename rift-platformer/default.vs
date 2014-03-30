#version 150

in vec2 vertexPosition;
in vec3 vertexColor;
in vec2 texCoords;

out vec4 fragColor;
out vec2 fragTexCoords;

out vec4 gl_Position;

void main()
{
    vec4 v = vec4(vertexPosition, 0, 1);
    gl_Position = v;

	fragColor = vec4(vertexColor, 1);
	fragTexCoords = texCoords;
}

