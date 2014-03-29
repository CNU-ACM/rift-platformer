#include "sprite_manager.h"

sprite_manager::sprite_manager()
{
}

void sprite_manager::add(const char* id, const char* fileName)
{
	sprites.insert(std::pair<std::string, Sprite*>(id, new Sprite(fileName)));
}

sf::Sprite* sprite_manager::getSprite(const char* id)
{
	return &sprites.find(id)->second->sprite;
}

void sprite_manager::remove(const char* id)
{
	sprites.erase(id);
}

void sprite_manager::Update(sf::RenderWindow* window)
{
	for (std::map<std::string, Sprite*>::iterator it = this->sprites.begin();
		it != this->sprites.end(); ++it)
	{
		it->second->Draw(window);
	}
}