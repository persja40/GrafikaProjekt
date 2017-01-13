#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "ProgramSettings.h"
#include "Image.h"
#include "Borderer.h"
int WindowWidth;
int WindowHeight;

std::vector<Image> images;

int main()
{
	ProgramSettings settings("settings.xml");
	WindowWidth = sf::VideoMode::getDesktopMode().width;
	WindowHeight = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "SFML works!", sf::Style::Fullscreen);
	
	for (int i = 0; i < settings.getImagesCount(); i++) {
		images.push_back(Image(settings.getImageSettings(i).getImageFilename()));
	}

	sf::Image bordered = Borderer::CreateBorder(images[0], Color::White, 10, 5, 100, 5).GenerateSfImage();

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

	return 0;
}