#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include <vector>
#include <string>
#include "sprite.h"

class sprite_manager
{
public:
	sprite_manager();

	void add(const char* id, const char* fileName, int width, int height);
	void add(const char* id, const char* fileName, const char* collisionFile, int width, int height);
	bool isFlippedH(const char* id);
	bool isFlippedV(const char* id);
	void flip(const char* id, bool flipH, bool flipV);
	void setFrame(const char* id, int frame);
	sf::Sprite* getSprite(const char* id);
	sf::Image* sprite_manager::getImage(const char* id);
	bool hasCollision(const char* id1, const char* id2);
	bool hasCollision(const char* id1, const char* id2, sf::Color &color1, sf::Color &color2);
	void remove(const char* id);

	void Update(sf::RenderWindow* window);
private:
	std::map<std::string, Sprite*> sprites;
	std::map<std::string, sf::Image> images;
};

#endif