#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "sprite_manager.h"

class game_state
{
public:
	game_state(sf::RenderWindow* renderWindow);
	void Update();
protected:
	sf::RenderWindow* renderWindow;
	sprite_manager spriteManager;
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
};

#endif
