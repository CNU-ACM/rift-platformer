#version 150

uniform mat4 perspTranslation;
uniform mat4 viewTranslation;
uniform mat4 rotMatrixX;
uniform mat4 rotMatrixY;
uniform vec2 scroll;

in vec3 vertexPosition;
in vec3 vertexColor;
in vec2 texCoords;

out vec4 gl_Position;
out vec4 fragColor;
out vec2 fragTexCoords;

void main()
{
    vec4 v = rotMatrixX * rotMatrixY * (vec4(-scroll, 0.0f, 0.0f) + vec4(vertexPosition, 1));
    gl_Position = perspTranslation * viewTranslation * v;

	fragColor = vec4(vertexColor, 1);
	fragTexCoords = texCoords;
}

