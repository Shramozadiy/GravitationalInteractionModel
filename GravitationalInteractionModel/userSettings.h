#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "initOpenGL.h"
#include "Resource.h"

class UserSettings
{
	UserSettings() {};
	UserSettings(const UserSettings&);
	UserSettings& operator=(UserSettings&) {};

	struct GraphicsSettings
	{
		int windowWidth;
		int windowHeight;
		int windowX;
		int windowY;

		bool vSync;
		int fps;
		int windowMode;
		int preferredScreen;
		int brightness;
	};

	struct SoundSettings
	{
		int totalVolume;
		int musicVolume;
		int gameVolume;
		int interfaceVolume;
		int alertVolume;
	};

	GraphicsSettings graphicsSettings = {};
	SoundSettings soundSettings = {};

public:

	static UserSettings& getInst();

	void loadSettings(std::string path);

	void saveSettings(std::string path);

	void setWindowPos(int x, int y, int width, int height);

	void setWindowMode(int mode);

	const GraphicsSettings& getGraphicsSettings();


};



