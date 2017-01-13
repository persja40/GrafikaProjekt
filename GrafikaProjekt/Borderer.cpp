#include "Borderer.h"

Image Borderer::CreateBorder(const Image& input, Color borderColor, const int topMargin, const int rightMargin, const int bottomMargin, const int leftMargin)
{
	const int width = input.getWidth() + leftMargin + rightMargin;
	const int height = input.getHeight() + topMargin + bottomMargin;

	Image bordered = Image(width, height);
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			Color color = borderColor;

			if (x > leftMargin && x < width - rightMargin &&
				y > topMargin   && y < height - bottomMargin)
			{

				int inputX = x - leftMargin;
				int inputY = y - topMargin;

				color = input.getPixel(inputX, inputY);
			}

			bordered.setPixel(x, y, color);
		}

	return bordered;
}

Image Borderer::CreateBorder(const Image& input, const std::string & text, Color borderColor, int horizontalMargin, int verticalMargin)
{
	return Image("ASDAS");
}
