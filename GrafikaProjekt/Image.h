#pragma once
#include <stdint.h>
#include <string>
#include "Color.h"
#include <SFML\Graphics.hpp>

class Image
{
public :
	Image(const int width, const int height);
	Image(const std::string& filename);


	sf::Image GenerateSfImage() const;

	inline Color getPixel(const int x, const int y) const;
	inline Color getPixel(const int index) const;

	inline void setPixel(const int x, const int y, const Color& val);
	inline void setPixel(const int index, const Color& val);

	inline int getWidth() const;
	int getHeight() const;
private:
	Color *pixels;
	int width;
	int height;
};

inline Color Image::getPixel(const int x, const int y) const
{
	return pixels[y * width + x];
}

inline Color Image::getPixel(const int index) const
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

inline int Image::getWidth() const
{
	return width;
}

inline int Image::getHeight() const
{
	return height;
}
