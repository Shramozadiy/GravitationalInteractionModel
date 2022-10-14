#include "Display.h"


Display& Display::getInst()
{
	static Display instance;
	return instance;
}

void Display::add(std::function<void(HWND, HDC, HGLRC)> ptr)
{
	displayProcedures.push_back(ptr);
}

void Display::run(HWND hwnd, HDC hDC, HGLRC hRC)
{
	for (auto i : displayProcedures)
	{
		i(hwnd, hDC, hRC);
	}
}
