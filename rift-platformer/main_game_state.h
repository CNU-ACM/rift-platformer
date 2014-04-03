#ifndef _TITLE_SCREEN_STATE_H_
#define _TITLE_SCREEN_STATE_H_

#include "game_state.h"
#include "MainGameManager.h"
#include <SFML/Audio.hpp>

#define MAIN_CHARACTER "mainCharacter"
#define MAIN_BACKGROUND1 "bg1"

class main_game : game_state
{
public:
	main_game(sf::RenderTexture* renderWindow);
	void setup();
	float scrollX, scrollY;
	void update();
	void draw();
private:
	sf::Music song;
	sf::SoundBuffer buffer;

	int fps = 0;
	int frame;
	int jumpCount;
	bool touchingGround;
	float gravity;
};

#endif