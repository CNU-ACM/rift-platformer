#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>

class Sprite
{
public:
	sf::Sprite sprite;
	bool flippedH, flippedV;

	Sprite();
	Sprite(const char* imageName);
	void load(const char* imageName);
	void Draw(sf::RenderWindow* window);
private:
	sf::Texture texture;
};

#endif