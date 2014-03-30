#include "game_state.h"
#include "title_screen_state.h"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <pv/OculusRift.h>
#include <pvmm/MidOpenGL.h>

using namespace PV;

GLuint _VRTexture;
GLuint _VRFBO;
GLuint _VRTexture2;
GLuint _VRFBO2;
unsigned int verticesBufferHandle;
unsigned int colorsBufferHandle;
unsigned int texCoordsBufferHandle;
unsigned int verticesArrayHandle;

void initQuad();

int main()
{
	OculusRift* rift;
	int width = 640;
	int height = 480;

	if (DetectDevice())
	{
		width = 1280;
		height = 800;
	}

	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 32;
	sf::RenderWindow window(sf::VideoMode(width, height), "Rift Platformer", sf::Style::Default, contextSettings);
	window.setActive();

	initMinGL();
	window.pushGLStates();
	glewInit();
	initQuad();
	unsigned int program = createShaders("vertexShader.vs", "fragShader.fs");
	rift = new OculusRift(false);
	float perspectiveMatrixLeft[16] = {
		0
	};
	float perspectiveMatrixRight[16] = {
		0
	};
	float viewMatrixLeft[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	float viewMatrixRight[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	if (rift->isConnected())
	{
		createPerspectiveMatrix(perspectiveMatrixLeft, rift->FieldOfView, rift->AspectRatio, 0.1f, 1000.0f);
		rift->ShiftView(Left, perspectiveMatrixLeft, viewMatrixLeft);

		createPerspectiveMatrix(perspectiveMatrixRight, rift->FieldOfView, rift->AspectRatio, 0.1f, 1000.0f);
		rift->ShiftView(Right, perspectiveMatrixRight, viewMatrixRight);
	}
	else
	{
		createPerspectiveMatrix(perspectiveMatrixLeft, 90.0f, 1280.0f / 800.0f, 0.1f, 1000.0f);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	window.popGLStates();
	window.resetGLStates();

	sf::RenderTexture texture;
	//texture.create(1280, 800);
	if (rift->isConnected())
	{
		texture.create(2048, 1080);
	}
	else
	{
		texture.create(640, 480);
	}
	game_state* mainState = new game_state(&texture);
	mainState = (game_state*)(new title_screen(&texture));
	bool start = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		window.pushGLStates();
		mainState->update();
		mainState->draw();
		texture.display();
		window.popGLStates();

		rift->Update();

		if (rift->isConnected() && !start)
		{
			//start = true;

			float angX = rift->GetRotation().x * M_PI / 180.0f;
			float angY = rift->GetRotation().y * M_PI / 180.0f;
			float rotMatrixX[16] = {
				1, 0, 0, 0,
				0, cos(angX), sin(angX), 0,
				0, -sin(angX), cos(angX), 0,
				0, 0, 0, 1
			};
			float rotMatrixY[16] = {
				cos(angY), 0, -sin(angY), 0,
				0, 1, 0, 0,
				sin(angY), 0, cos(angY), 0,
				0, 0, 0, 1
			};

			int perspCore = 0;
			int perspTranslation = 0;
			int viewTranslation = 0;
			int rotX = 0, rotY = 0;

			glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, 640, 800);
			pv_glUseProgram(program);
			perspTranslation = pv_glGetUniformLocation(program, "perspTranslation");
			pv_glUniformMatrix4fv(perspTranslation, 1, false, perspectiveMatrixLeft);
			viewTranslation = pv_glGetUniformLocation(program, "viewTranslation");
			glUniform4f(viewTranslation, viewMatrixLeft[12], 0, 0, 1);
			rotX = pv_glGetUniformLocation(program, "rotMatrixX");
			pv_glUniformMatrix4fv(rotX, 1, false, rotMatrixX);
			rotY = pv_glGetUniformLocation(program, "rotMatrixY");
			pv_glUniformMatrix4fv(rotY, 1, false, rotMatrixY);
			pv_glUniform2f(pv_glGetUniformLocation(program, "scroll"),
				((title_screen*)mainState)->scrollX / 6720.0f * 100.0f,
				((title_screen*)mainState)->scrollY / 1088.0f * 100.0f);
			sf::Texture::bind(&texture.getTexture());
			glBindVertexArray(verticesArrayHandle);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO2);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, 640, 800);
			pv_glUseProgram(program);
			perspTranslation = pv_glGetUniformLocation(program, "perspTranslation");
			pv_glUniformMatrix4fv(perspTranslation, 1, false, perspectiveMatrixRight);
			viewTranslation = pv_glGetUniformLocation(program, "viewTranslation");
			glUniform4f(viewTranslation, viewMatrixLeft[12], 0, 0, 0);
			rotX = pv_glGetUniformLocation(program, "rotMatrixX");
			pv_glUniformMatrix4fv(rotX, 1, false, rotMatrixX);
			rotY = pv_glGetUniformLocation(program, "rotMatrixY");
			pv_glUniformMatrix4fv(rotY, 1, false, rotMatrixY);
			pv_glUniform2f(pv_glGetUniformLocation(program, "scroll"),
				((title_screen*)mainState)->scrollX / 6720.0f * 100.0f, 
				((title_screen*)mainState)->scrollY / 1088.0f * 100.0f);
			sf::Texture::bind(&texture.getTexture());
			glBindVertexArray(verticesArrayHandle);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(97.0f / 255.0f, 160.0f / 255.0f, 227.0f / 255.0f, 255.0f / 255.0f);
			rift->ComposeFinalImage(_VRTexture, _VRTexture2);
		}
		else
		{
			window.draw(sf::Sprite(texture.getTexture()));
		}

		window.display();
	}

	return EXIT_SUCCESS;
}

void initQuad()
{
	float quadVerts[4 * 3] = {
		-0.0f, -10.0f, -5.0f,
		-0.0f, 10.0f, -5.0f,
		100.0f, -10.0f, -5.0f,
		100.0f, 10.0f, -5.0f
	};
	float quadColor[4 * 3] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	float quadTexture[4 * 2] = {
		0.0, 0.0,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	// Create the vertex array handle.
	glGenVertexArrays(1, &verticesArrayHandle);
	glBindVertexArray(verticesArrayHandle);

	// Create the vertices buffer.
	glGenBuffers(1, &verticesBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &colorsBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, colorsBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadColor), quadColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &texCoordsBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordsBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadTexture), quadTexture, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	glGenTextures(1, &_VRTexture);
	glBindTexture(GL_TEXTURE_2D, _VRTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &_VRFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _VRTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO);

	glGenTextures(1, &_VRTexture2);
	glBindTexture(GL_TEXTURE_2D, _VRTexture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 640, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenFramebuffers(1, &_VRFBO2);
	glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO2);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _VRTexture2, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, _VRFBO2);
}
