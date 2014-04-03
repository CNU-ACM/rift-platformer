#include "sprite.h"

Sprite::Sprite() : Drawable()
{
}

Sprite::Sprite(const char* imageName, int width, int height) : Drawable(imageName, width, height)
{
}


