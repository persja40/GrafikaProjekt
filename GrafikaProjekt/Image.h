#pragma once
#include <stdint.h>
#include <string>
#include <cstring>
#include "Color.h"
#include <SFML\Graphics.hpp>
#include <memory>
class Image
{
public :
	Image(const int width, const int height);
	Image(const std::string& filename);
	Image(const sf::Image& image);
	
	
	//void drawOn(Image& other, int x, int y);
	
	void free();
	void setAlpha(uint8_t value);
	void setAlphaForNotTransparent(uint8_t value);
	void changeAlpha(float ratio);

	// size must be the same
	void fastAssign(const Image & source);
	Image copy();

	sf::Image GenerateSfImage() const;

	inline Color getPixel(const int x, const int y) const;
	inline Color getPixel(const int index) const;

	inline uint8_t * getPixmap() const;

	inline void setPixel(const int x, const int y, const Color& val);
	inline void setPixel(const int index, const Color& val);

	inline int getWidth() const;
	inline int getHeight() const;

private:
	void loadFromImage(const sf::Image &image);
	Color* pixels;
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

inline uint8_t * Image::getPixmap() const
{
	return (uint8_t *) this->pixels;
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
