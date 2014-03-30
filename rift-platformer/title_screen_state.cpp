#include "title_screen_state.h"

title_screen::title_screen(sf::RenderWindow* renderWindow) : game_state(renderWindow)
{
	spriteManager.add("logo", "graphics/title_screen/MainSprite.png", "graphics/title_screen/bounds.png");
	spriteManager.add("logo2", "graphics/title_screen/logo.png");

	spriteManager.getSprite("logo")->setPosition(256, 256);
}
void title_screen::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		spriteManager.getSprite("logo")->move(-1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		spriteManager.getSprite("logo")->move(1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		spriteManager.getSprite("logo")->move(0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		spriteManager.getSprite("logo")->move(0, 1);
	}
	sf::Color c;
	spriteManager.hasCollision("logo", "logo2", c, sf::Color());
	if (c.r == 255 && c.g == 0 && c.b == 0)
	{
		spriteManager.getSprite("logo")->move(1, 0);
	}
	if (c.r == 255 && c.g == 255 && c.b == 0)
	{
		spriteManager.getSprite("logo")->move(-1, 0);
	}
	if (c.r == 0 && c.g == 255 && c.b == 0)
	{
		spriteManager.getSprite("logo")->move(0, 1);
	}
	if (c.r == 0 && c.g == 0 && c.b == 255)
	{
		spriteManager.getSprite("logo")->move(0, -1);
	}
}
void title_screen::draw()
{
	if (spriteManager.hasCollision("logo", "logo2"))
	{
		this->renderWindow->clear(sf::Color::Red);
	}
	else
	{
		this->renderWindow->clear(sf::Color::Black);
	}

	// do other graphics here.

	spriteManager.Update(this->renderWindow);
}