#include "Events.h"

Events& Events::getInst() {
	static Events instance;
	return instance;
}

void Events::add(std::function<void(HWND, UINT, WPARAM, LPARAM)> ptr)
{
	eventsProcedure.push_back(ptr);
}

void Events::run(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	for (auto i : eventsProcedure)
	{
		i(hWnd, msg, wp, lp);
	}
}
