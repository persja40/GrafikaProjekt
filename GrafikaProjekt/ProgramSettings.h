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


private :
	void loadImageSettings(tinyxml2::XMLNode* node);
	std::vector<ImageSettings> imageSettings;
	bool frameEnabled;
	programMode mode;


};