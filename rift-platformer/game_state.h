#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "sprite_manager.h"

class game_state
{
public:
	game_state(sf::RenderTexture* renderWindow);
	void Update();
	virtual void handleEvents();
	virtual void update();
	virtual void draw();
protected:
	sf::RenderTexture* renderWindow;
	sprite_manager spriteManager;
};

#endif
