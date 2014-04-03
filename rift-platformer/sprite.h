#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "drawable.h"

class Sprite : public Drawable
{
public:
	Sprite();
	Sprite(const char* imageName, int width, int height);
private:
};

#endif