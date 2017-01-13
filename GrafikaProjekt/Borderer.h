#pragma once
#include "Image.h"

namespace Borderer
{
	Image CreateBorder(const Image& input, Color borderColor, const int topMagin, const int rightMargin, const int bottom, const int leftMargin);
	Image CreateBorder(const Image& input, const std::string& text, Color borderColor, int horizontalMargin, int verticalMargin);


};