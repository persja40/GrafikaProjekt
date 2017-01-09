#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "ProgramSettings.h"

int WindowWidth;
int WindowHeight;
std::vector<sf::Image> sfImages;
int main()
{
	ProgramSettings settings("settings.xml");
	WindowWidth = sf::VideoMode::getDesktopMode().width;
	WindowHeight = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "SFML works!", sf::Style::Fullscreen);
	
	for (int i = 0; i < settings.getImagesCount(); i++) {
		sfImages.push_back(sf::Image());
		sfImages.back().loadFromFile(settings.getImageSettings(i).getImageFilename());
	}
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
		window.display();
	}

	return 0;
}