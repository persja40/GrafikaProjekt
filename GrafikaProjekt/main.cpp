#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "ProgramSettings.h"
#include "Image.h"
#include "Global.h"
#include "Borderer.h"
#include "AlternativeBlender.h"
#include "ImageTransformator.h"
#include <time.h>
#include <stdio.h>
#include <random>
int WindowWidth;
int WindowHeight;

//#define FPS_CHECK 
#define DEBUG_MEMORY_LEAK 0
#include "Blendable.h"
//#include <vld.h>

std::vector<Image> images;

int random(int min, int max)
{
	return min + rand() % (max - min);
}

float random(float min, float max)
{
	return min + (max - min) * (rand() % 1001) / 1000.f;
}

int main()
{
	Global::font.loadFromFile("font.ttf");

	ProgramSettings settings("settings.xml");
	WindowWidth = sf::VideoMode::getDesktopMode().width;
	WindowHeight = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "SFML works!", sf::Style::Fullscreen);



	// prescale
	for (int i = 0; i < settings.getImagesCount(); i++) {
		Image tmp(settings.getImageSettings(i).getImageFilename());
		Image scaled = ImageTransformator::rescaleImage(tmp, sf::Vector2i(settings.getImageSettings(i).getImageSize().x, settings.getImageSettings(i).getImageSize().y));

		//images.push_back(scaled);
		if (settings.isFrameEnabled())
		{
			images.push_back(Borderer::CreateBorder(scaled, settings.getImageSettings(i).getImageDescription(), settings.getImageSettings(i).getFrameColor(),  10, 5, 100, 5));
			scaled.free();
		}
		else
		{
			images.push_back(scaled);
		}

		tmp.free();
	}

	// background set
	Image background(WindowWidth, WindowHeight);
	if (settings.getBackground() != "")
	{
		background.free();
		background = Image(settings.getBackground());
	}
	Image backroundScaled = ImageTransformator::rescaleImage(background, sf::Vector2i(WindowWidth, WindowHeight));
	background.free();

	Image screen(WindowWidth, WindowHeight);
	Image buffer(WindowWidth, WindowHeight);

	buffer.fastAssign(backroundScaled);
	
	sf::Texture texture;
	sf::Sprite sprite;
	
	srand(34);
	std::vector <float> rotations;
	for (int i = 0; i < images.size();i++) {
		rotations.push_back(2.0*M_PI*((float)rand()) / ((float)RAND_MAX));
		images.at(i).setAlphaForNotTransparent(255);
	}

	float ct=0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			}

		}

		ct += 0.01;
		// fps inspection
#ifdef FPS_CHECK
		double begin = (double)clock() / (double)CLOCKS_PER_SEC;
#endif 

		// example render procedure
		screen.fastAssign(buffer);
		static int currentImage = 0;
		static float alpha = 0;
		static float delay = 0;
		std::vector<Blendable> blendables;
		bool memorize = false;
		switch (settings.getProgramMode())
		{
		case programMode::Normal:
		{
			auto current = Blendable(ImageTransformator::applyScaleAndCentralRotation(images.at(currentImage), settings.getImageSettings(currentImage).getRotation(), 1.0, 1.0), settings.getImageSettings(currentImage).getImageCenter().x, settings.getImageSettings(currentImage).getImageCenter().y);
			current.image.changeAlpha(alpha);
			blendables.push_back(current);

			if (alpha >= 1)
			{
				delay += settings.getSpeed();
				if (currentImage < images.size() - 1 && delay >= settings.getDelay())
				{
					memorize = true;
					currentImage = (currentImage + 1);
					alpha = 0.0;
					delay = 0.0;
				}
			}
			else
			{
				alpha+= 0.01 * settings.getSpeed();
			}
			break;
		}
		case programMode::Random:
		{
			static float zoom = random(1.5f, 2.f);
			static float x = random(0, WindowWidth);
			static float y = random(0, WindowHeight);
			static float rotation = random(0.f, M_PI);

			auto current = Blendable(ImageTransformator::applyScaleAndCentralRotation(images.at(currentImage), rotation, zoom, zoom), x, y);
			blendables.push_back(current);

			if (zoom <= 1)
			{
				zoom = 1.f;
				delay += settings.getSpeed();
				if (delay >= settings.getDelay())
				{
					memorize = true;
					currentImage = (currentImage + 1) % images.size();
					zoom = random(2.f, 5.f);
					x = random(0, WindowWidth);
					y = random(0, WindowHeight);
					delay = 0.0;
				}
			}
			else
			{
				zoom -= 0.05 * settings.getSpeed();
				rotation += random(0.02f,0.05f) * settings.getSpeed();
			}

			



			break;
		}
		}
		// prepare image in blending order
		
		/*for (int i = 0; i < images.size(); i++) {
			blendables.push_back(Blendable(ImageTransformator::applyScaleAndCentralRotation(images.at(i),ct,0.5,0.5),settings.getImageSettings(i).getImageCenter().x, settings.getImageSettings(i).getImageCenter().y));
			break;
		}*/
		
		AlternativeBlender::BlendOnImage(screen, blendables);
		for (int i = 0; i < blendables.size(); i++) {
			blendables.at(i).image.free();
			break;
		}

		if (memorize)
		{
			buffer.fastAssign(screen);
		}

		//sent to GPU and render
		texture.loadFromImage(screen.GenerateSfImage());
		sprite.setTexture(texture, true);

		//window.clear();
		window.draw(sprite);
		window.display();

		

		//fps inspection
#ifdef FPS_CHECK
		double result = 1.0 / ((double)clock() / (double)CLOCKS_PER_SEC - begin);
		std::cout << "FPS: " << result<<std::endl;
#endif
	}

	for (int i = 0;i < images.size();++i)
		images[i].free();
	backroundScaled.free();
	screen.free();
	return 0;
}