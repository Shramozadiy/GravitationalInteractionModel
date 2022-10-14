#pragma once


#include <Windows.h>

#include <vector>
#include <functional>

class Display
{
	Display() {};
	Display(const Display&);
	Display& operator=(Display&) {};

	std::vector<std::function<void(HWND, HDC, HGLRC)>> displayProcedures;

public:

	static Display& getInst();

	void add(std::function<void(HWND, HDC, HGLRC)> ptr);

	void run(HWND hwnd, HDC hDC, HGLRC hRCp);
};

