#include "sprite.h"

Sprite::Sprite()
{
	this->flippedH = false;
	this->flippedV = false;
}

Sprite::Sprite(const char* imageName)
{
	if (!this->texture.loadFromFile(imageName))
	{
		printf("error loading texture!");
	}
	else
	{
		this->sprite = sf::Sprite(this->texture);
	}
	this->flippedH = false;
	this->flippedV = false;
}

void Sprite::load(const char* imageName)
{
	if (!this->texture.loadFromFile(imageName))
	{
		printf("error loading texture!");
	}
	else
	{
		this->sprite = sf::Sprite(this->texture);
	}
}

void Sprite::Draw(sf::RenderWindow* window)
{
	window->draw(this->sprite);
}