#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include <vector>
#include <string>
#include "sprite.h"

class sprite_manager
{
public:
	sprite_manager();

	void add(const char* id, const char* fileName);
	sf::Sprite* getSprite(const char* id);
	void remove(const char* id);

	void Update(sf::RenderWindow* window);
private:
	std::map<std::string, Sprite*> sprites;
};

#endif