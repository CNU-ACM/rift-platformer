#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include <vector>
#include <string>
#include "sprite.h"
#include "background.h"

class object_manager
{
public:
	object_manager();

	void addSprite(const char* id, const char* fileName, int width, int height);
	void addSprite(const char* id, const char* fileName, const char* collisionFile, int width, int height);

	void addBg(const char* id, const char* fileName, int width, int height);
	void addBg(const char* id, const char* fileName, const char* collisionFile, int width, int height);

	bool isFlippedH(const char* id);
	bool isFlippedV(const char* id);
	void flip(const char* id, bool flipH, bool flipV);
	void setFrame(const char* id, int frame);

	Sprite* getSprite(const char* id);
	Background* getBackground(const char* id);

	sf::Image* getImage(const char* id);

	bool hasCollision(const char* id1, const char* id2);
	bool hasCollision(const char* id1, const char* id2, sf::Color &color1, sf::Color &color2);
	void remove(const char* id);

	void Update(sf::RenderTexture* window);
private:
	std::map<std::string, Drawable*> sprites;
	std::map<std::string, sf::Image> images;
};

#endif