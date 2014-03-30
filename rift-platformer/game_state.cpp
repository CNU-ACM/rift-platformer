#include "game_state.h"

game_state::game_state(sf::RenderTexture* renderWindow)
{
	this->renderWindow = renderWindow;
}

void game_state::Update()
{
	this->handleEvents();
	this->update();
	this->draw();

	this->renderWindow->display();
}

void game_state::handleEvents()
{
}
void game_state::update()
{
}
void game_state::draw()
{
	this->renderWindow->clear(sf::Color::Black);
}


