#pragma once

#include "tinyxml2.h"
#include "ProgramMode.h"
#include "ImageSettings.h"
#include <vector>
#include <string>

class ProgramSettings
{
public :
	ProgramSettings(std::string settingsFilename);

	void loadProgramSettings(tinyxml2::XMLNode* node);
	int getImagesCount();
	ImageSettings getImageSettings(int node);
	
	std::string getBackground() const { return background; }
	programMode getProgramMode() const { return mode; }
	bool isFrameEnabled() const { return frameEnabled; }
	float getSpeed() const { return speed; }
	float getDelay() const { return delay; }

private :
	void loadImageSettings(tinyxml2::XMLNode* node);
	std::vector<ImageSettings> imageSettings;
	bool frameEnabled;
	programMode mode;
	std::string background;
	float speed;
	float delay;


};