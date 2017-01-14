#include "Color.h"

Color Color::White = { 255, 255, 255 };

void Color::blendWith(const Color & other, float otherAlpha)
{

	blendWith(other, 1.f - otherAlpha, otherAlpha);

}

void Color::blendWith(const Color & other,const float myAlpha,const float otherAlpha)
{
	float denominator = otherAlpha + myAlpha * (1 - otherAlpha);

	r = (uint8_t)((float)other.r * otherAlpha + myAlpha * (1.f - otherAlpha) * (float)r) / denominator;
	g = (uint8_t)((float)other.g * otherAlpha + myAlpha * (1.f - otherAlpha)  * (float)g) / denominator;
	b = (uint8_t)((float)other.b * otherAlpha + myAlpha * (1.f - otherAlpha)  * (float)b) / denominator;

}
