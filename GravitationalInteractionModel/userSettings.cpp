#include "userSettings.h"

UserSettings& UserSettings::getInst() {
	static UserSettings instance;
	return instance;
}

void UserSettings::loadSettings(std::string path)
{
	graphicsSettings.windowX = 50;
	graphicsSettings.windowY = 50;
	graphicsSettings.windowWidth = 500;
	graphicsSettings.windowHeight = 500;
	graphicsSettings.vSync = true;
	graphicsSettings.fps = 60;
	graphicsSettings.brightness = 50;
	graphicsSettings.preferredScreen = 0;
	graphicsSettings.windowMode = 0;

	soundSettings.totalVolume = 50;
	soundSettings.musicVolume = 50;
	soundSettings.gameVolume = 50;
	soundSettings.interfaceVolume = 50;
	soundSettings.alertVolume = 50;

	std::string line;

	std::ifstream in(path);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			std::cout << line << std::endl;

			std::string key;
			std::string value;

			if (std::find(line.cbegin(), line.cend(), '=') == line.cend())
				continue;

			std::copy(line.cbegin(), std::find(line.cbegin(), line.cend(), '='), std::back_inserter(key));
			std::copy(std::find(line.cbegin(), line.cend(), '=') + 1, line.cend(), std::back_inserter(value));
			
			if (key == "windowX")
				graphicsSettings.windowX = stoi(value);
			else if (key == "windowY")
				graphicsSettings.windowY = stoi(value);
			else if (key == "windowWidth")
				graphicsSettings.windowWidth = stoi(value);
			else if (key == "windowHeight")
				graphicsSettings.windowHeight = stoi(value);
			else if (key == "vSync")
				graphicsSettings.vSync = (bool)stoi(value);
			else if (key == "fps")
				graphicsSettings.fps = stoi(value);
			else if (key == "brightness")
				graphicsSettings.brightness = stoi(value);
			else if (key == "preferredScreen")
				graphicsSettings.preferredScreen = stoi(value);
			else if (key == "windowMode")
				graphicsSettings.windowMode = stoi(value);

			else if (key == "totalVolume")
				soundSettings.totalVolume = stoi(value);
			else if (key == "musicVolume")
				soundSettings.musicVolume = stoi(value);
			else if (key == "gameVolume")
				soundSettings.gameVolume = stoi(value);
			else if (key == "interfaceVolume")
				soundSettings.interfaceVolume = stoi(value);
			else if (key == "alertVolume")
				soundSettings.alertVolume = stoi(value);

		}
	}

	in.close();

	setWindowPos(graphicsSettings.windowX, graphicsSettings.windowY, graphicsSettings.windowWidth, graphicsSettings.windowHeight);
	set_vsync(graphicsSettings.vSync);
	setWindowMode(graphicsSettings.windowMode);
}

void UserSettings::saveSettings(std::string path)
{
	std::ofstream out; // поток для записи
	out.open(path);	   // окрываем файл для записи

	if (out.is_open())
	{
		out << "[GraphicsSettings]" << std::endl;
		out << "windowX" << "=" << graphicsSettings.windowX << std::endl;
		out << "windowY" << "=" << graphicsSettings.windowY << std::endl;
		out << "windowWidth" << "=" << graphicsSettings.windowWidth << std::endl;
		out << "windowHeight" << "=" << graphicsSettings.windowHeight << std::endl;
		out << "vSync" << "=" << graphicsSettings.vSync << std::endl;
		out << "fps" << "=" << graphicsSettings.fps << std::endl;
		out << "brightness" << "=" << graphicsSettings.brightness << std::endl;
		out << "preferredScreen" << "=" << graphicsSettings.preferredScreen << std::endl;
		out << "windowMode" << "=" << graphicsSettings.windowMode << std::endl;

		out << "[SoundSettings]" << std::endl;
		out << "totalVolume" << "=" << soundSettings.totalVolume << std::endl;
		out << "musicVolume" << "=" << soundSettings.musicVolume << std::endl;
		out << "gameVolume" << "=" << soundSettings.gameVolume << std::endl;
		out << "interfaceVolume" << "=" << soundSettings.interfaceVolume << std::endl;
		out << "alertVolume" << "=" << soundSettings.alertVolume << std::endl;
	}

	out.close();
}

void UserSettings::setWindowPos(int x, int y, int width, int height)
{
	graphicsSettings.windowX = x;
	graphicsSettings.windowY = y;
	graphicsSettings.windowWidth = width;
	graphicsSettings.windowHeight = height;

	HWND hWnd = FindWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME);

	SetWindowPos(hWnd, HWND_TOP, x, y, width, height, SWP_SHOWWINDOW);

	saveSettings("settings.ini");
}

void UserSettings::setWindowMode(int mode)
{
	HWND hWnd = FindWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME);

	switch (mode)
	{
	case 0: // Полноэкранный режим
		SetWindowLongPtr(hWnd, GWL_STYLE, 0);
		SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowWindow(hWnd, SW_SHOWMAXIMIZED);
		break;
	case 1: // Оконный режим
		SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, graphicsSettings.windowX, graphicsSettings.windowY, graphicsSettings.windowWidth, graphicsSettings.windowHeight, SWP_SHOWWINDOW);
		//ShowWindow(hWnd, SW_SHOWNORMAL);
		break;
	case 2:
		break;
	default:
		break;
	}
	
}

const UserSettings::GraphicsSettings& UserSettings::getGraphicsSettings()
{
	return graphicsSettings;
}
