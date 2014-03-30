#include "title_screen_state.h"

title_screen::title_screen(sf::RenderWindow* renderWindow) : game_state(renderWindow)
{
	spriteManager.add("logo", "graphics/title_screen/MainSprite.png", "graphics/title_screen/bounds.png");
	spriteManager.add("logo2", "graphics/title_screen/testBg.png");

	gravity = 0.0f;
	this->touchingGround = false;
}
void title_screen::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		spriteManager.getSprite("logo")->move(-1, 0);
		spriteManager.flip("logo", true, false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		spriteManager.getSprite("logo")->move(1, 0);
		spriteManager.flip("logo", false, false);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		spriteManager.getSprite("logo")->move(0, -8);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}

	spriteManager.getSprite("logo")->move(0, gravity);
	if (!this->touchingGround && gravity < 10.0f)
	{
		gravity += 0.1f;
	}

	sf::Color c;
	bool hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());

	while (hasCollision && c.r == 255 && c.g == 255 && c.b == 0)
	{
		if (spriteManager.isFlippedH("logo"))
		{
			spriteManager.getSprite("logo")->move(1, 0);
		}
		else
		{
			spriteManager.getSprite("logo")->move(-1, 0);
		}
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
	}
	while (hasCollision && c.r == 255 && c.g == 0 && c.b == 0)
	{
		if (spriteManager.isFlippedH("logo"))
		{
			spriteManager.getSprite("logo")->move(-1, 0);
		}
		else
		{
			spriteManager.getSprite("logo")->move(1, 0);
		}
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
	}

	if (hasCollision)
	{
		spriteManager.getSprite("logo")->move(0, 1);
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
		gravity = 0.0f;
	}
	while (hasCollision)
	{
		spriteManager.getSprite("logo")->move(0, -1);
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
		gravity = 0.0f;
	}

	spriteManager.getSprite("logo")->move(0, 1);
	if (spriteManager.hasCollision("logo", "logo2", sf::Color(), sf::Color()))
	{
		this->touchingGround = true;
	}
	else
	{
		this->touchingGround = false;
	}
	spriteManager.getSprite("logo")->move(0, -1);

	sf::Vector2f pos1 = spriteManager.getSprite("logo")->getPosition();
	sf::Vector2f pos2 = spriteManager.getSprite("logo2")->getPosition();

	if (pos1.y > this->renderWindow->getSize().y - 256 &&
		-pos2.y < spriteManager.getSprite("logo2")->getTexture()->getSize().y
		- this->renderWindow->getSize().y)
	{
		spriteManager.getSprite("logo")->move(0, -1);
		spriteManager.getSprite("logo2")->move(0, -1);
	}
	if (pos1.y < 256 &&
		pos2.y < 0)
	{
		spriteManager.getSprite("logo")->move(0, 1);
		spriteManager.getSprite("logo2")->move(0, 1);
	}

	if (pos1.x > this->renderWindow->getSize().x - 512 &&
		-pos2.x < spriteManager.getSprite("logo2")->getTexture()->getSize().x
		- this->renderWindow->getSize().x)
	{
		spriteManager.getSprite("logo")->move(-1, 0);
		spriteManager.getSprite("logo2")->move(-1, 0);
	}
	if (pos1.x < 256 &&
		pos2.x < 0)
	{
		spriteManager.getSprite("logo")->move(1, 0);
		spriteManager.getSprite("logo2")->move(1, 0);
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
		this->renderWindow->clear(sf::Color::Blue);
	}

	// do other graphics here.

	spriteManager.Update(this->renderWindow);
}