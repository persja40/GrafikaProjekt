#include "Color.h"

Color Color::White = { 255, 255, 255 };

void Color::blendWith(const Color & other, float otherAlpha)
{

	blendWith(other, 1.f - otherAlpha, otherAlpha);

}

void Color::blendWith(const Color & other,const float myAlpha,const float otherAlpha)
{

	r = (uint8_t)((float)r * myAlpha + otherAlpha * (1.f - myAlpha) * (float)other.r);
	g = (uint8_t)((float)g * myAlpha + otherAlpha * (1.f - myAlpha)  * (float)other.g);
	b = (uint8_t)((float)b * myAlpha+ otherAlpha * (1.f - myAlpha)  * (float)other.b);

}
