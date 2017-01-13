#pragma once
#include "Image.h"

namespace Borderer
{
	Image CreateBorder(const Image& input, const Color& borderColor, const int topMagin, const int rightMargin, const int bottom, const int leftMargin);
	Image CreateBorder(const Image& input, const std::string & text, const Color& borderColor, const int topMargin, const int rightMargin, const int bottomMargin, const int leftMargin);


};