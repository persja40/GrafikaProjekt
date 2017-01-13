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
		int r = *(pixelPtr + 0);
		int g = *(pixelPtr + 1);
		int b = *(pixelPtr + 2);
		int a = *(pixelPtr + 3);

		pixels[i].r = r;
		pixels[i].g = g;
		pixels[i].b = b;
		pixels[i].a = a;

		pixelPtr += 4;
	}
}


sf::Image Image::GenerateSfImage() const
{
	sf::Image image;
	sf::Uint8 *pixels = new sf::Uint8[width * height * 4];
	for (int i = 0; i < width * height; ++i)
	{
		auto col = getPixel(i);
		pixels[i * 4 + 0] = col.r;
		pixels[i * 4 + 1] = col.g;
		pixels[i * 4 + 2] = col.b;
		pixels[i * 4 + 3] = col.a;
	}

	image.create(width, height, pixels);

	return image;

	delete[] pixels;
}

