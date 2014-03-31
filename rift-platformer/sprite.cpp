#include "sprite.h"

Sprite::Sprite()
{
	this->flippedH = false;
	this->flippedV = false;
}

Sprite::Sprite(const char* imageName, int width, int height)
{
	this->load(imageName, width, height);
}

void Sprite::Flip(bool flipH, bool flipV)
{
	if (this->flippedH != flipH)
	{
		if (flipH)
		{
			this->sprite.setScale(-1.0f, 1.0f);
			this->sprite.move(-this->width / 2, 0);
		}
		else
		{
			this->sprite.setScale(1.0f, 1.0f);
			this->sprite.move(this->width / 2, 0);
		}
	}

	this->flippedH = flipH;
	this->flippedV = flipV;
}

void Sprite::load(const char* imageName, int width, int height)
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
	this->width = width;
	this->height = height;

	this->setFrame(0);
	this->sprite.setOrigin(this->width / 2, this->height / 2);
	this->sprite.move(this->width / 2, this->height / 2);
}

void Sprite::Draw(sf::RenderTexture* window)
{
	window->draw(this->sprite);
}

void Sprite::setFrame(int frame)
{
	int x = 0;
	int y = 0;
	while (frame * this->width > this->sprite.getTexture()->getSize().x - this->width)
	{
		y += this->height;
		frame -= (this->sprite.getTexture()->getSize().x / this->width);
	}
	x = frame * this->width;
	this->sprite.setTextureRect(sf::IntRect(x, y, this->width, this->height));
}