#pragma once
#include <stdint.h>
#include <string>
#include "Color.h"


class Image
{
public :
	Image(const int width, const int height);
	Image(const std::string& filename);
	
	inline Color getPixel(const int x, const int y);
	inline Color getPixel(const int index);

	inline void setPixel(const int x, const int y, const Color& val);
	inline void setPixel(const int index, const Color& val);

	inline int getWidth();
	inline int getHeight();
private:
	Color *pixels;
	int width;
	int height;
};