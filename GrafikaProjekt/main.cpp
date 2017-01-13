#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "ProgramSettings.h"
#include "Image.h"
#include "Global.h"
#include "Borderer.h"
int WindowWidth;
int WindowHeight;

#define DEBUG_MEMORY_LEAK 1

#include <vld.h>

std::vector<Image> images;

int main()
{
	Global::font.loadFromFile("font.ttf");

	ProgramSettings settings("settings.xml");
	WindowWidth = sf::VideoMode::getDesktopMode().width;
	WindowHeight = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "SFML works!", sf::Style::Fullscreen);
	
	for (int i = 0; i < settings.getImagesCount(); i++) {
		images.push_back(Image(settings.getImageSettings(i).getImageFilename()));
	}

	auto imgB = Borderer::CreateBorder(images[0], "Siema Eniu", Color::White, 10, 5, 100, 5);
	sf::Image bordered = imgB.GenerateSfImage();

	sf::Texture texture;
	texture.loadFromImage(bordered);
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	sprite.setPosition(300, 100);
	
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
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

		window.clear();
		window.draw(shape);
		window.draw(sprite);
		window.display();
	}

	for (int i = 0;i < images.size();++i)
		images[i].free();
	imgB.free();
	return 0;
}