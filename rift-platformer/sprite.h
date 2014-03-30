#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics.hpp>

class Sprite
{
public:
	sf::Sprite sprite;
	bool flippedH, flippedV;

	Sprite();
	Sprite(const char* imageName, int width, int height);
	void load(const char* imageName, int width, int height);
	void Draw(sf::RenderWindow* window);

	void Flip(bool flipH, bool flipV);
	void setFrame(int frame);
private:
	sf::Texture texture;
	int width, height;
};

#endif