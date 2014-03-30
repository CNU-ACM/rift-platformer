#include "title_screen_state.h"

title_screen::title_screen(sf::RenderWindow* renderWindow) : game_state(renderWindow)
{
	spriteManager.add("logo", "graphics/title_screen/MainSprite.png", "graphics/title_screen/bounds.png", 128, 134);
	spriteManager.add("logo2", "graphics/title_screen/testBg.png", 6720, 1088);

	frame = 0;
	gravity = 0.0f;
	this->touchingGround = false;
	this->jumpCount = 0;
}
void title_screen::update()
{
	spriteManager.setFrame("logo", 8);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		spriteManager.getSprite("logo")->move(-1, 0);
		spriteManager.flip("logo", true, false);
		spriteManager.setFrame("logo", this->frame);
		if (fps >= 60)
		{
			if (this->frame > 3)
			{
				this->frame = 0;
			}
			else
			{
				this->frame += 1;
			}
			fps = 0;
		}
		else
		{
			fps += 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		spriteManager.getSprite("logo")->move(1, 0);
		spriteManager.flip("logo", false, false);
		spriteManager.setFrame("logo", this->frame);
		if (fps >= 60)
		{
			if (this->frame > 3)
			{
				this->frame = 0;
			}
			else
			{
				this->frame += 1;
			}
			fps = 0;
		}
		else
		{
			fps += 1;
		}
	}
	if (!this->touchingGround)
	{
		spriteManager.setFrame("logo", 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->touchingGround && this->jumpCount < 1)
	{
		this->gravity = -2.5f;
		this->jumpCount = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
	}

	sf::Color c;
	bool hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());

	while (hasCollision && (c.r == 255 && c.g == 255 && c.b == 0))
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
	while (hasCollision && (c.r == 255 && c.g == 0 && c.b == 0))
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

	if (hasCollision && c.r == 0 && c.g == 255 && c.b == 0 && !this->touchingGround)
	{
		spriteManager.getSprite("logo")->move(0, 1);
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
		this->gravity = 0.0f;
	}
	while (hasCollision && c.r == 0 && c.g == 0 && c.b == 255)
	{
		spriteManager.getSprite("logo")->move(0, -1);
		hasCollision = spriteManager.hasCollision("logo", "logo2", c, sf::Color());
		gravity = 0.0f;
	}

	spriteManager.getSprite("logo")->move(0, 1);
	if (spriteManager.hasCollision("logo", "logo2", c, sf::Color()) && c.r == 0 && c.g == 0 && c.b == 255)
	{
		this->touchingGround = true;
		this->jumpCount = 0;
	}
	else
	{
		this->touchingGround = false;
	}
	spriteManager.getSprite("logo")->move(0, -1);

	spriteManager.getSprite("logo")->move(0, gravity);
	if (!this->touchingGround && gravity < 7.0f)
	{
		gravity += 0.025f;
	}

	sf::Vector2f pos1 = spriteManager.getSprite("logo")->getPosition();
	sf::Vector2f pos2 = spriteManager.getSprite("logo2")->getPosition();

	if (pos1.y > this->renderWindow->getSize().y - (this->renderWindow->getSize().y * 0.25) &&
		-pos2.y < spriteManager.getSprite("logo2")->getTextureRect().height
		- this->renderWindow->getSize().y)
	{
		spriteManager.getSprite("logo")->move(0, -1);
		spriteManager.getSprite("logo2")->move(0, -1);
	}
	if (pos1.y < (this->renderWindow->getSize().y * 0.25) &&
		pos2.y < 0)
	{
		spriteManager.getSprite("logo")->move(0, 1);
		spriteManager.getSprite("logo2")->move(0, 1);
	}

	if (pos1.x > this->renderWindow->getSize().x - (this->renderWindow->getSize().x * 0.25) &&
		-pos2.x < spriteManager.getSprite("logo2")->getTextureRect().width
		- this->renderWindow->getSize().x)
	{
		spriteManager.getSprite("logo")->move(-1, 0);
		spriteManager.getSprite("logo2")->move(-1, 0);
	}
	if (pos1.x < (this->renderWindow->getSize().x * 0.25) &&
		pos2.x < 0)
	{
		spriteManager.getSprite("logo")->move(1, 0);
		spriteManager.getSprite("logo2")->move(1, 0);
	}
}
void title_screen::draw()
{
	sf::Color sky;
	sky.r = 97;
	sky.g = 160;
	sky.b = 227;
	this->renderWindow->clear(sky);

	// do other graphics here.

	spriteManager.Update(this->renderWindow);
}