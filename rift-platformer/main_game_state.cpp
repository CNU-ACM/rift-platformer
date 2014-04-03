#include "main_game_state.h"

main_game::main_game(sf::RenderTexture* renderWindow) : game_state(renderWindow)
{
	this->setup();
	this->objectManager = MainGameManager();
	song.openFromFile("music/song_main.wav");
	song.setLoop(true);
	song.play();
	//buffer.loadFromFile("death.wav");
}

void main_game::setup()
{
	objectManager.addSprite(MAIN_CHARACTER, "graphics/title_screen/MainSprite.png", "graphics/title_screen/bounds.png", 128, 134);
	//objectManager.add(MAIN_BACKGROUND1, "graphics/title_screen/testBg.png", 1600, 800);
	objectManager.addBg(MAIN_BACKGROUND1, "graphics/title_screen/detailedbg.png", "graphics/title_screen/collisionmap.png", 6720, 1088);

	frame = 0;
	gravity = 0.0f;
	scrollX = 0.0f;
	scrollY = -50.0f;
	this->touchingGround = false;
	this->jumpCount = 0;
}
#define FPS 15
void main_game::update()
{
	sf::Vector2f pos1 = objectManager.getSprite(MAIN_CHARACTER)->sprite.getPosition();
	sf::Vector2f pos2 = objectManager.getBackground(MAIN_BACKGROUND1)->sprite.getPosition();
	scrollX = (objectManager.getSprite(MAIN_CHARACTER)->sprite.getPosition().x / renderWindow->getSize().x)
		* objectManager.getBackground(MAIN_BACKGROUND1)->sprite.getTexture()->getSize().x;

	if (pos1.y > this->renderWindow->getSize().y - (this->renderWindow->getSize().y * 0.25) &&
		-pos2.y < objectManager.getBackground(MAIN_BACKGROUND1)->sprite.getTextureRect().height
		- this->renderWindow->getSize().y)
	{
		objectManager.getSprite(MAIN_CHARACTER)->sprite.move(0, -1);
		objectManager.getBackground(MAIN_BACKGROUND1)->sprite.move(0, -1);
	}
	if (pos1.y < (this->renderWindow->getSize().y * 0.25) &&
		pos2.y < 0)
	{
		objectManager.getSprite(MAIN_CHARACTER)->sprite.move(0, 1);
		objectManager.getBackground(MAIN_BACKGROUND1)->sprite.move(0, 1);
	}

	if (pos1.x > this->renderWindow->getSize().x - (this->renderWindow->getSize().x * 0.25) &&
		-pos2.x < objectManager.getBackground(MAIN_BACKGROUND1)->sprite.getTextureRect().width
		- this->renderWindow->getSize().x)
	{
		objectManager.getSprite(MAIN_CHARACTER)->sprite.move(-1, 0);
		objectManager.getBackground(MAIN_BACKGROUND1)->sprite.move(-1, 0);
	}
	if (pos1.x < (this->renderWindow->getSize().x * 0.25) &&
		pos2.x < 0)
	{
		objectManager.getSprite(MAIN_CHARACTER)->sprite.move(1, 0);
		objectManager.getBackground(MAIN_BACKGROUND1)->sprite.move(1, 0);
	}

	if (pos1.y > objectManager.getBackground(MAIN_BACKGROUND1)->sprite.getTexture()->getSize().y)
	{
		objectManager.remove(MAIN_CHARACTER);
		objectManager.remove(MAIN_BACKGROUND1);
		this->setup();
	}
}
void main_game::draw()
{
	sf::Color sky;
	sky.r = 97;
	sky.g = 160;
	sky.b = 227;
	this->renderWindow->clear(sky);

	// do other graphics here.

	objectManager.Update(this->renderWindow);
}