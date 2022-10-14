#include "InitGame.h"

#include "Display.h"
#include "Events.h"
#include "initOpenGL.h"
#include "Factory.h"
#include "Camera.h"
#include "Planet.h"

std::function<void(void)> ptrGameDestructor;

void initGame()
{
	

	glClearColor(0, 0, 0, 1);

	Factory<Camera<double>>& cameras = Factory<Camera<double>>::getInst();

	double n = 5;
	double k = 0.05;

	// Инициализация планет 
	Factory<Planet>& planets = Factory<Planet>::getInst();
	Planet sun({ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 19891 * pow(10, 5), k * log(109 + n));
	Planet mercury({ 0, 0.46, 0 }, { 48682 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 330.2, k * log(0.38 + n));
	Planet venus({ 0, 1.082, 0 }, { 35020 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 4868.5, k * log(0.95 + n));
	Planet earth({ 0, 1.496, 0 }, { 29782 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 5973.6, k * log(1 + n));
	Planet mars({ 0, 2.28, 0 }, { 24130 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 641.85, k * log(0.53 + n));

	Planet jupiter({ 0, 8.16, 0 }, { 13070 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 1898600, k * log(10.97+n));
	Planet saturn({ 0, 14.29, 0 }, { 9670 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 568460, k * log(9.14+n));
	Planet uranium({ 0, 28.76, 0 }, { 6810 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 86832, k * log(3.981+n));
	Planet neptune({ 0, 45.03, 0 }, { 5430 * pow(10, -5.5),0, 0 }, { 0, 0, 0 }, 102430, k * log(3.965+n));
	planets.add(sun);
	planets.add(mercury);
	planets.add(venus);
	planets.add(earth);
	planets.add(mars);
	planets.add(jupiter);
	planets.add(saturn);
	planets.add(uranium);
	planets.add(neptune);

	// Инициализация камеры
	Position<double> cameraPos = { 0, 0, 0.0 };
	Camera<double> camera1(cameraPos, 1.0, 0.01);
	cameras.add(camera1);
	auto setCameraPos = [&cameras](HWND hWnd, HDC hDC, HGLRC hRC) {cameras[0].setPosition({ 0.0, 0.0, 0.0 }); };
	auto enableCamera1 = [&cameras](HWND hWnd, HDC hDC, HGLRC hRC) { cameras[0].enable(); };

	auto mouseWheel1 = [&cameras](HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) { cameras[0].mouseWheel(hWnd, msg, wp, lp); };
	auto mouseMove1 = [&cameras](HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) { cameras[0].mouseMove(hWnd, msg, wp, lp); };


	Camera<double> camera2({ 0, 0, 0 }, 1.0, 0.01);
	cameras.add(camera2);
	auto enableCamera2 = [&cameras](HWND hWnd, HDC hDC, HGLRC hRC) { cameras[1].enable(); };


	// Добавлние графики
	//Display::getInst().add(setCameraPos);
	Display::getInst().add(enableCamera1);

	for (int i = 0; i < planets.size(); i++)
	{
		planets[i].draw();
	}

	Display::getInst().add(enableCamera2);

	// Добавление событий
	Events::getInst().add(mouseWheel1);
	Events::getInst().add(mouseMove1);

	ptrGameDestructor = []()
	{
	};
}

void gameDestructor()
{
	ptrGameDestructor();
}