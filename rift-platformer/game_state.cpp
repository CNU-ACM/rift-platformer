#include "game_state.h"

game_state::game_state(sf::RenderWindow* renderWindow)
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
	sf::Event event;
	while (this->renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->renderWindow->close();
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
		{
			this->renderWindow->close();
		}
	}
}
void game_state::update()
{
}
void game_state::draw()
{
	this->renderWindow->clear(sf::Color::Black);
}


