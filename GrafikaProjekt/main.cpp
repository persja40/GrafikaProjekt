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
#define DEBUG_MEMORY_LEAK 1
#include "Blendable.h"
//#include <vld.h>

std::vector<Image> images;

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
		Image scaled = ImageTransformator::rescaleImage(tmp, sf::Vector2i(settings.getImageSettings(i).getImageSize().x*2, settings.getImageSettings(i).getImageSize().y*2));
		
		//images.push_back(scaled);
		// TODO add if 
		images.push_back(Borderer::CreateBorder(scaled, settings.getImageSettings(i).getImageDescription(), Color::White, 10, 5, 100, 5));
		scaled.free();
		tmp.free();
	}

	// background set
	Image background("piasek.jpg");	
	Image backroundScaled = ImageTransformator::rescaleImage(background, sf::Vector2i(1024, 700));
	background.free();

	Image screen(1024, 700);

	sf::Texture texture;
	sf::Sprite sprite;
	
	srand(34);
	std::vector <float> rotations;
	for (int i = 0; i < images.size();i++) {
		rotations.push_back(2.0*M_PI*((float)rand()) / ((float)RAND_MAX));
		images.at(i).setAlphaForNotTransparent(200);
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
		screen.fastAssign(backroundScaled);

		// prepare image in blending order
		std::vector<Blendable> blendables;
		for (int i = 0; i < images.size(); i++) {
			blendables.push_back(Blendable(ImageTransformator::applyScaleAndCentralRotation(images.at(i),ct,0.5,0.5),settings.getImageSettings(i).getImageCenter().x, settings.getImageSettings(i).getImageCenter().y));
		}
		
		AlternativeBlender::BlendOnImage(screen, blendables);
		for (int i = 0; i < images.size(); i++) {
			blendables.at(i).image.free();
		}

		

		//sent to GPU and render
		texture.loadFromImage(screen.GenerateSfImage());
		sprite.setTexture(texture, true);

		window.clear();
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