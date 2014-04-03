#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <SFML/Graphics.hpp>

class Drawable
{
public:
	sf::Sprite sprite;
	bool flippedH, flippedV;

	Drawable();
	Drawable(const char* imageName, int width, int height);
	void load(const char* imageName, int width, int height);
	void Draw(sf::RenderTexture* window);

	void Flip(bool flipH, bool flipV);
	void setFrame(int frame);

	virtual const char* type()
	{
		return "drawable";
	};
private:
	sf::Texture texture;
	int width, height;
};


#endif