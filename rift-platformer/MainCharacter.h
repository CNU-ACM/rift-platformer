#ifndef _MAIN_CHARACTER_H_
#define _MAIN_CHARACTER_H_

#define MAIN_CHARACTER "mainCharacter"
#define COLLISION_BACKGROUND "bg1"

#include "sprite.h"
#include "object_manager.h"

class MainCharacter : public Sprite
{
public:
	MainCharacter(object_manager* objectManager);
	MainCharacter(object_manager* objectManager, const char* imageName, int width, int height);
	void Update();
private:
	int fps = 0;
	int frame;
	int jumpCount;
	bool touchingGround;
	float gravity;

	object_manager* objectManager;

	void updateControls();
	void updatePhysics();
};

#endif


