#include "Borderer.h"
#include <SFML\Graphics.hpp>
#include "Global.h"

Image Borderer::CreateBorder(const Image& input, const Color& borderColor, const int topMargin, const int rightMargin, const int bottomMargin, const int leftMargin)
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

//Musiałem tutaj użyć SFML niestety
Image Borderer::CreateBorder(const Image& input, const std::string & text, const Color& borderColor,  const int topMargin, const int rightMargin, const int bottomMargin, const int leftMargin)
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

				Color imageColor = input.getPixel(inputX, inputY);
				float alpha = imageColor.a;
				alpha /= 255.0;
				
				color.r = (1.0-alpha)*((float) color.r)+alpha*((float)imageColor.r);
				color.g = (1.0 - alpha)*((float)color.g) + alpha*((float)imageColor.g);
				color.b = (1.0 - alpha)*((float)color.b) + alpha*((float)imageColor.b);
				color.a = 255;
			}

			bordered.setPixel(x, y, color);
		}

	

	sf::Text sfText;
	sfText.setString(text);
	sfText.setFillColor(sf::Color(255 - borderColor.r,255-  borderColor.g,255 - borderColor.b, 255));
	sfText.setFont(Global::font);
	

	sf::RenderTexture texture;
	texture.create(sfText.getLocalBounds().width, sfText.getLocalBounds().height);
	texture.clear(sf::Color(borderColor.r, borderColor.g, borderColor.b, borderColor.a));

	texture.draw(sfText);
	texture.display();

	Image textImage(texture.getTexture().copyToImage());

	for(int y = 0; y < textImage.getHeight(); ++y)
		for (int x = 0; x < textImage.getWidth(); ++x)
		{
			int transX = (width - sfText.getLocalBounds().width) / 2;
			int transY = (topMargin + input.getHeight()) + (bottomMargin - sfText.getLocalBounds().height) / 2;


			auto test = textImage.getPixel(x, y);
			bordered.setPixel(transX + x, transY + y, textImage.getPixel(x, y));
		}
	textImage.free();
	return bordered;

}
