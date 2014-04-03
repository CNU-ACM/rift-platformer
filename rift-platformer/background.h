#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "drawable.h"

class Background : public Drawable
{
public:
	Background();
	Background(const char* imageName, int width, int height);
private:
};

#endif