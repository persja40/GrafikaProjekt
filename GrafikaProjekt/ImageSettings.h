#pragma once
#include <SFML\System\Vector2.hpp>
#include <string>
#include "tinyxml2.h"


class ImageSettings
{
public :
	 ImageSettings(tinyxml2::XMLNode* node);
private :
	std::string filename;
	std::string description;

	sf::Vector2f center;
	sf::Vector2f size;
	
	float rotation;

};