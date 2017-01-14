#include "Image.h"
#include <SFML/Graphics.hpp>

Image::Image(const int width, const int height)
{
	this->width = width;
	this->height = height;
	pixels = new Color[width * height];
	alpha = 1.0;
}

Image::Image(const std::string& filename)
{
	sf::Image image = sf::Image();
	image.loadFromFile(filename);

	loadFromImage(image);
}

Image::Image(const sf::Image& image)
{
	loadFromImage(image);
}

void Image::drawOn(Image & other, int transX, int transY)
{
	int width = getWidth();
	int height = getHeight();

	int otherWidth = other.getWidth();
	int otherHeight = other.getHeight();

	for (int y = 0; y < getHeight(); ++y)
		for (int x = 0; x < getWidth(); ++x)
		{
			if (transX + x >= otherWidth)
				throw "Motyla noga";
			if (transY + y >= otherHeight)
				throw "Niech to dunder swisnie";

			other.blendPixel(transX + x, transY + y, getPixel(x, y), alpha);
		}
}


void Image::loadFromImage(const sf::Image & image)
{
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
		alpha = a / 255.f;

		pixelPtr += 4;
	}
}

void Image::free()
{
	delete[]pixels;
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
		pixels[i * 4 + 3] = alpha * 255;
	}

	image.create(width, height, pixels);
	delete[] pixels;
	return image;
}

sf::RenderTexture* Image::GenerateRenderTexture() const
{
	sf::RenderTexture *rTexture = new sf::RenderTexture();
	sf::Uint8 *pixels = new sf::Uint8[width * height * 4];
	for (int i = 0; i < width * height; ++i)
	{
		auto col = getPixel(i);
		pixels[i * 4 + 0] = col.r;
		pixels[i * 4 + 1] = col.g;
		pixels[i * 4 + 2] = col.b;
		pixels[i * 4 + 3] = alpha;
	}

	sf::Texture *texture = new sf::Texture();
	texture->create(width, height);
	texture->loadFromImage(GenerateSfImage());
	
	
	delete[] pixels;

	return rTexture;

	
}

