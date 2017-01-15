#include "Blendable.h"

Blendable::Blendable(Image & t_image, int centerX, int centerY):image(t_image)
{
	this->centerX = centerX;
	this->centerY = centerY;
}

Blendable::~Blendable()
{
}
