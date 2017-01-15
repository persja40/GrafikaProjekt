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
	if (centerNode != nullptr)
	{
		center.x = std::stof(centerNode->FirstChildElement("x")->GetText());
		center.y = std::stof(centerNode->FirstChildElement("y")->GetText());
	}
	else
	{
		center.x = 0;
		center.y = 0;
	}
	DEBUG_(center.x); DEBUG_(", "); DEBUG(center.y);

	DEBUG_("size = ");
	auto sizeNode = node->FirstChildElement("size");
	size.x = std::stof(sizeNode->FirstChildElement("x")->GetText());
	size.y = std::stof(sizeNode->FirstChildElement("y")->GetText());
	DEBUG_(size.x); DEBUG_(", "); DEBUG(size.y);
	auto rotationNode = node->FirstChildElement("rotation");
	if(rotationNode != nullptr)
		rotation = std::stof(rotationNode->GetText()) * M_PI / 180  ;
	rotation = 0.f;

	DEBUG("Loading description");
	auto descriptionNode = node->FirstChildElement("description");
	if (descriptionNode != nullptr)
	{
		description = node->FirstChildElement("description")->GetText();
		DEBUG(description);
	}
	else
		DEBUG("decription - not found");

	DEBUG("Loading frame");
	auto frameNode = node->FirstChildElement("frame");
	if (frameNode != nullptr)
	{
		frameColor.r = std::stof(frameNode->FirstChildElement("r")->GetText());
		frameColor.g = std::stof(frameNode->FirstChildElement("g")->GetText());
		frameColor.b = std::stof(frameNode->FirstChildElement("b")->GetText());
		frameColor.a = 255;
	}
	else
		DEBUG("Frame not found");

	

}

std::string ImageSettings::getImageFilename()
{
	return std::string(filename);
}

std::string ImageSettings::getImageDescription()
{
	return std::string(description);
}

sf::Vector2i ImageSettings::getImageCenter()
{
	return sf::Vector2i(center);
}

sf::Vector2i ImageSettings::getImageSize()
{
	return sf::Vector2i(size);
}

float ImageSettings::getRotation()
{
	return rotation;
}

Color ImageSettings::getFrameColor()
{
	return frameColor;
}
