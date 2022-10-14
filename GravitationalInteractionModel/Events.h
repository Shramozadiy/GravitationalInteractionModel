#pragma once

#include <Windows.h>

#include <vector>
#include <functional>

class Events
{
	Events() {};
	Events(const Events&);
	Events& operator=(Events&) {};

	std::vector<std::function<void(HWND, UINT, WPARAM, LPARAM)>> eventsProcedure;

public:

	static Events& getInst();

	void add(std::function<void(HWND, UINT, WPARAM, LPARAM)>);

	void run(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};




