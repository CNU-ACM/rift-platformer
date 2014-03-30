#ifndef _TITLE_SCREEN_STATE_H_
#define _TITLE_SCREEN_STATE_H_

#include "game_state.h"

class title_screen : game_state
{
public:
	title_screen(sf::RenderWindow* renderWindow);
private:
	int fps = 0;
	int frame;
	int jumpCount;
	bool touchingGround;
	float gravity;
	void update();
	void draw();
};

#endif