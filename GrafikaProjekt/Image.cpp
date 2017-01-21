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

	loadFromImage(image);
}

Image::Image(const sf::Image& image)
{
	loadFromImage(image);
}


void Image::loadFromImage(const sf::Image & image)
{
	auto size = image.getSize();
	width = size.x;
	height = size.y;

	pixels = new Color[width * height];

	memcpy(pixels, image.getPixelsPtr(), width*height * 4);
}

void Image::free()
{
	delete[]pixels;
}

void Image::setAlpha(uint8_t value)
{
	uint8_t *pixmap = getPixmap();
	for (unsigned i = 3; i < getWidth()*getHeight()*4;) {
		pixmap[i] = value;
		i = i + 4;
	}
}

void Image::setAlphaForNotTransparent(uint8_t value)
{
	uint8_t *pixmap = getPixmap();
	for (unsigned i = 3; i < getWidth()*getHeight()*4;) {
		if (pixmap[i]) {
			pixmap[i] = value;
		}
		i = i + 4;
	}
}

void Image::changeAlpha(float ratio)
{
	uint8_t *pixmap = getPixmap();
	for (unsigned i = 3; i < getWidth()*getHeight()*4;) {
		pixmap[i] = (((float)pixmap[i])*ratio)>255?255:((float)pixmap[i])*ratio;
		i = i + 4;
	}
}

void Image::fastAssign(const Image & source)
{
	memcpy(getPixmap(), source.getPixmap(), width*height * 4);
}

Image Image::copy()
{
	Image my_copy(width, height);
	memcpy(my_copy.getPixmap(), getPixmap(), width*height * 4);
	return my_copy;
}


sf::Image Image::GenerateSfImage() const
{
	sf::Image image;
	image.create(width, height, getPixmap());
	return image;
}



