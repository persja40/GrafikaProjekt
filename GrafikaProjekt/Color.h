#pragma once
#include <stdint.h>

struct Color
{
	uint8_t r, g, b;

	static Color White;

	void blendWith(const Color& other, const float otherAlpha);
	void blendWith(const Color& other, float myAlpha, float otherAlpha);

};