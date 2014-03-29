#include "title_screen_state.h"

title_screen::title_screen(sf::RenderWindow* renderWindow) : game_state(renderWindow)
{
	spriteManager.add("logo", "graphics/title_screen/logo.png");
}

void title_screen::draw()
{
	this->renderWindow->clear(sf::Color::Black);

	// do other graphics here.

	spriteManager.Update(this->renderWindow);
}