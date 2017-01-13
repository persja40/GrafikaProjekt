#include "ImageSettings.h"
#include "defines.h"
#include "Debug.h"
#include <iostream>

using namespace tinyxml2;

ImageSettings::ImageSettings(XMLNode * node)
{
	DEBUG_("filename = ");
	filename = node->FirstChildElement("filename")->GetText();
	DEBUG(filename);

	DEBUG_("center = ");
	auto centerNode = node->FirstChildElement("center");
	center.x = std::stof(centerNode->FirstChildElement("x")->GetText());
	center.y = std::stof(centerNode->FirstChildElement("y")->GetText());
	DEBUG_(center.x); DEBUG_(", "); DEBUG(center.y);

	DEBUG_("size = ");
	auto sizeNode = node->FirstChildElement("size");
	size.x = std::stof(sizeNode->FirstChildElement("x")->GetText());
	size.y = std::stof(sizeNode->FirstChildElement("y")->GetText());
	DEBUG_(size.x); DEBUG_(", "); DEBUG(size.y);
	rotation = std::stof(node->FirstChildElement("rotation")->GetText()) * 180 / M_PI;

	DEBUG("Loading description");
	auto descriptionNode = node->FirstChildElement("description");
	if (descriptionNode != nullptr)
	{
		description = node->FirstChildElement("description")->GetText();
		DEBUG(description);
	}
	else
		DEBUG("decription - not found");

	

}

std::string ImageSettings::getImageFilename()
{
	return std::string(filename);
}

std::string ImageSettings::getImageDescription()
{
	return std::string(description);
}

sf::Vector2f ImageSettings::getImageCenter()
{
	return sf::Vector2f(center);
}

sf::Vector2f ImageSettings::getImageSize()
{
	return sf::Vector2f(size);
}
