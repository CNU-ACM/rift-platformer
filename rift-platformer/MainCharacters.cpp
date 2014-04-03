#include "MainCharacter.h"

MainCharacter::MainCharacter(object_manager* objectManager) : Sprite()
{
	this->objectManager = objectManager;
}
MainCharacter::MainCharacter(object_manager* objectManager, const char* imageName, int width, int height) : Sprite(imageName, width, height)
{
	this->objectManager = objectManager;
}

void MainCharacter::Update()
{
	this->updateControls();
	this->updatePhysics();
}

void MainCharacter::updateControls()
{ 
	objectManager->setFrame(MAIN_CHARACTER, 8);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && objectManager->getSprite(MAIN_CHARACTER)->sprite.getPosition().x > 0)
	{
		objectManager->getSprite(MAIN_CHARACTER)->sprite.move(-1, 0);
		objectManager->flip(MAIN_CHARACTER, true, false);
		objectManager->setFrame(MAIN_CHARACTER, this->frame);
		if (fps >= 15)
		{
			if (this->frame > 3)
			{
				this->frame = 0;
			}
			else
			{
				this->frame += 1;
			}
			fps = 0;
		}
		else
		{
			fps += 1;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		objectManager->getSprite(MAIN_CHARACTER)->sprite.move(1, 0);
		objectManager->flip(MAIN_CHARACTER, false, false);
		objectManager->setFrame(MAIN_CHARACTER, this->frame);
		if (fps >= 15)
		{
			if (this->frame > 3)
			{
				this->frame = 0;
			}
			else
			{
				this->frame += 1;
			}
			fps = 0;
		}
		else
		{
			fps += 1;
		}
	}
	if (!this->touchingGround)
	{
		objectManager->setFrame(MAIN_CHARACTER, 5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->touchingGround && this->jumpCount < 1)
	{
		this->gravity = -2.5f;
		this->jumpCount = 1;
	}
}

void MainCharacter::updatePhysics()
{
	sf::Color c;
	bool hasCollision = objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color());

	while (hasCollision && (c.r == 255 && c.g == 255 && c.b == 0))
	{
		if (objectManager->isFlippedH(MAIN_CHARACTER))
		{
			objectManager->getSprite(MAIN_CHARACTER)->sprite.move(1, 0);
		}
		else
		{
			objectManager->getSprite(MAIN_CHARACTER)->sprite.move(-1, 0);
		}
		hasCollision = objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color());
	}
	while (hasCollision && (c.r == 255 && c.g == 0 && c.b == 0))
	{
		if (objectManager->isFlippedH(MAIN_CHARACTER))
		{
			objectManager->getSprite(MAIN_CHARACTER)->sprite.move(-1, 0);
		}
		else
		{
			objectManager->getSprite(MAIN_CHARACTER)->sprite.move(1, 0);
		}
		hasCollision = objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color());
	}

	if (hasCollision && c.r == 0 && c.g == 255 && c.b == 0 && !this->touchingGround)
	{
		objectManager->getSprite(MAIN_CHARACTER)->sprite.move(0, 1);
		hasCollision = objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color());
		this->gravity = 0.0f;
	}
	while (hasCollision && c.r == 0 && c.g == 0 && c.b == 255)
	{
		objectManager->getSprite(MAIN_CHARACTER)->sprite.move(0, -1);
		hasCollision = objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color());
		gravity = 0.0f;
	}

	objectManager->getSprite(MAIN_CHARACTER)->sprite.move(0, 1);
	if (objectManager->hasCollision(MAIN_CHARACTER, COLLISION_BACKGROUND, c, sf::Color()) && c.r == 0 && c.g == 0 && c.b == 255)
	{
		this->touchingGround = true;
		this->jumpCount = 0;
	}
	else
	{
		this->touchingGround = false;
	}
	objectManager->getSprite(MAIN_CHARACTER)->sprite.move(0, -1);

	objectManager->getSprite(MAIN_CHARACTER)->sprite.move(0, gravity);
	if (!this->touchingGround && gravity < 7.0f)
	{
		gravity += 0.040f;
	}
}


