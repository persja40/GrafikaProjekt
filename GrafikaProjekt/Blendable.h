#pragma once

#include "Image.h"

struct Blendable {
	Image image;
	int centerX, centerY;
	Blendable(Image & image, int centerX, int centerY);
	~Blendable();
};