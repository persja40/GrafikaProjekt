#pragma once
#include <SFML\System\Vector2.hpp>
#include <string>
#include "tinyxml2.h"
#include "Color.h"

class ImageSettings
{
public :
	 ImageSettings(tinyxml2::XMLNode* node);
	 std::string getImageFilename();
	 std::string getImageDescription();
	 sf::Vector2i getImageCenter();
	 sf::Vector2i getImageSize();
	 float getRotation();
	 Color getFrameColor();
private :
	std::string filename;
	std::string description;

	sf::Vector2i center;
	sf::Vector2i size;
	Color frameColor;
	
	float rotation;

};