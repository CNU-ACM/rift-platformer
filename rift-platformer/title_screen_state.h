#ifndef _TITLE_SCREEN_STATE_H_
#define _TITLE_SCREEN_STATE_H_

#include "game_state.h"
#include <SFML/Audio.hpp>

class title_screen : game_state
{
public:
	title_screen(sf::RenderTexture* renderWindow);
	void setup();
	float scrollX, scrollY;
	void update();
	void draw();
private:
	sf::Music song;
	sf::SoundBuffer buffer;
	int fps = 0;
	float posX;
	int frame;
	int jumpCount;
	bool touchingGround;
	float gravity;
};

#endif