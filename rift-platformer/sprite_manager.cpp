#include "sprite_manager.h"

sprite_manager::sprite_manager()
{
}

void sprite_manager::add(const char* id, const char* fileName, int width, int height)
{
	sprites.insert(std::pair<std::string, Sprite*>(id, new Sprite(fileName, width, height)));
	images.insert(std::pair<std::string, sf::Image>(id, this->getSprite(id)->getTexture()->copyToImage()));
}
void sprite_manager::add(const char* id, const char* fileName, const char* collisionFile, int width, int height)
{
	sprites.insert(std::pair<std::string, Sprite*>(id, new Sprite(fileName, width, height)));

	images.insert(std::pair<std::string, sf::Image>(id, sf::Image()));
	this->getImage(id)->loadFromFile(collisionFile);
}

bool sprite_manager::isFlippedH(const char* id)
{
	return sprites.find(id)->second->flippedH;
}
bool sprite_manager::isFlippedV(const char* id)
{
	return sprites.find(id)->second->flippedV;
}

void sprite_manager::flip(const char* id, bool flipH, bool flipV)
{
	Sprite* sprite = sprites.find(id)->second;

	if (flipH != sprite->flippedH)
	{
		images.find(id)->second.flipHorizontally();
	}
	if (flipV != sprite->flippedV)
	{
		images.find(id)->second.flipVertically();
	}

	sprite->Flip(flipH, flipV);
}

void sprite_manager::setFrame(const char* id, int frame)
{
	this->sprites.find(id)->second->setFrame(frame);
}

sf::Sprite* sprite_manager::getSprite(const char* id)
{
	return &sprites.find(id)->second->sprite;
}
sf::Image* sprite_manager::getImage(const char* id)
{
	return &images.find(id)->second;
}

bool sprite_manager::hasCollision(const char* id1, const char* id2)
{
	return this->hasCollision(id1, id2, sf::Color(), sf::Color());
}

bool sprite_manager::hasCollision(const char* id1, const char* id2, sf::Color &color1, sf::Color &color2)
{
	sf::Sprite* sprite1 = this->getSprite(id1);
	sf::Sprite* sprite2 = this->getSprite(id2);

	sf::Vector2f original1 = sprite1->getScale();
	sf::Vector2f original2 = sprite2->getScale();

	sprite1->setScale(abs(sprite1->getScale().x), abs(sprite1->getScale().y));
	sprite2->setScale(abs(sprite2->getScale().x), abs(sprite2->getScale().y));

	sf::Transform t1 = sprite1->getTransform();
	sf::Transform t2 = sprite2->getTransform();

	sf::Image* i1 = this->getImage(id1);
	sf::Image* i2 = this->getImage(id2);

	sf::Transform transformed = t1 * t2.getInverse();

	for (int yA = 0; yA < sprite1->getTextureRect().height; yA += 1)
	{
		for (int xA = 0; xA < sprite1->getTextureRect().width; xA += 1)
		{
			sf::Vector2f positionIn2 = transformed.transformPoint(xA, yA);

			int x = positionIn2.x;
			int y = positionIn2.y;

			if (0 <= x && x < sprite2->getTextureRect().width &&
				0 <= y && y < sprite2->getTextureRect().height)
			{
				sf::Color c1 = i1->getPixel(xA, yA);
				sf::Color c2 = i2->getPixel(x, y);

				if (c1.a != 0 && c2.a != 0)
				{
					color1 = c1;
					color2 = c2;
					sprite1->setScale(original1);
					sprite2->setScale(original2);
					return true;
				}
			}
		}
	}
	sprite1->setScale(original1);
	sprite2->setScale(original2);
	return false;
}

void sprite_manager::remove(const char* id)
{
	sprites.erase(id);
	images.erase(id);
}

void sprite_manager::Update(sf::RenderTexture* window)
{
	for (std::map<std::string, Sprite*>::iterator it = this->sprites.begin();
		it != this->sprites.end(); ++it)
	{
		it->second->Draw(window);
	}
}