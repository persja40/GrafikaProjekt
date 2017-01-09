#include "ProgramSettings.h"
#include <string>
#include <iostream>
#include "Debug.h"

using namespace tinyxml2;

using std::string;

ProgramSettings::ProgramSettings(std::string settingsFilename)
{
	DEBUG("Wczytuje " + settingsFilename);
	XMLDocument doc(true, COLLAPSE_WHITESPACE);
	doc.LoadFile(settingsFilename.c_str());
	if (doc.Error())
	{
		DEBUG("BLAD!");
		exit(-1);
	}

	XMLNode *root = doc.FirstChildElement("settings");

	
	loadProgramSettings(root->FirstChildElement("program"));
	DEBUG("---------");
	loadImageSettings(root->FirstChildElement("images"));
}

void ProgramSettings::loadProgramSettings(tinyxml2::XMLNode * node)
{
	DEBUG("Wczytuje ustawienia programu");
	auto test = node->FirstChildElement("frame");

	DEBUG_("Frame = ");
	string frame = node->FirstChildElement("frame")->GetText();
	DEBUG(frame);

	frameEnabled = (frame == "true");
	DEBUG_("mode = ");
	int modeValue = std::stoi(node->FirstChildElement("mode")->GetText());
	DEBUG(modeValue);

	switch (modeValue)
	{
	case 1:
		mode = programMode::Normal;
		break;
	case 2:
		mode = programMode::Smooth;
		break;
	case 3:
		mode = programMode::Random;
		break;
	}

}

int ProgramSettings::getImagesCount()
{
	return static_cast<int>(imageSettings.size());
}

ImageSettings ProgramSettings::getImageSettings(int node)//throws out_of_range
{
	return imageSettings.at(node);
}

void ProgramSettings::loadImageSettings(XMLNode * node)
{
	XMLNode* imageNode = node->FirstChildElement("image");

	int i = 1;

	while (imageNode != nullptr)
	{
		DEBUG_("Wczytuje obrazek nr. ");
		DEBUG(i);
		ImageSettings settings(imageNode);
		imageSettings.push_back(settings);

		imageNode = imageNode->NextSiblingElement("image");
		++i;
		DEBUG("---------");
	}
}
