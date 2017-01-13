#include "Image.h"
#include <SFML/Graphics.hpp>

Image::Image(const int width, const int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width * height];
}

Image::Image(const std::string& filename)
{
	sf::Image image = sf::Image();
	image.loadFromFile(filename);

	auto size = image.getSize();
	width = size.x;
	height = size.y;

	pixels = new Color[width * height];

	const sf::Uint8 *pixelPtr = image.getPixelsPtr();

	for (int i = 0; i < width * height; ++i)
	{
		int r = *pixelPtr;
		int g = *(++pixelPtr);
		int b = *(++pixelPtr);
		int a = *(++pixelPtr);

		pixels[i].r = r;
		pixels[i].g = g;
		pixels[i].b = b;
		pixels[i].a = a;
	}

}


inline Color Image::getPixel(const int x, const int y)
{
	return pixels[y * width + x];
}

inline Color Image::getPixel(const int index)
{
	return pixels[index];
}

inline void Image::setPixel(const int x, const int y, const Color& val)
{
	pixels[y * width + x] = val;
}

inline void Image::setPixel(const int index, const Color& val)
{
	pixels[index] = val;
}

inline int Image::getWidth()
{
	return width;
}

inline int Image::getHeight()
{
	return height;
}
