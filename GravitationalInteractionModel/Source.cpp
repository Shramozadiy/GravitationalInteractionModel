// Для настройки проекта необходимо пройти по пути: Проект -> Свойства -> Компоновщик -> Система 
// И в пунтке Подсистема выбрать "Windows (/SUBSYSTEM:WINDOWS)"
//

#include <Windows.h>
#include <gl/GL.h>
#include <chrono>
#include <thread>
#include <vector>



#include "initOpenGL.h"
#include "userSettings.h"
#include "Events.h"
#include "Display.h"
#include "InitGame.h"
#include "MyGeometry/MyGeometry.h"
#include "LogicCycle.h"
#include "Resource.h"

#pragma comment (lib, "opengl32.lib")

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void initGame();
void gameDestructor();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass))
		return -1;

	HWND hWnd = CreateWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME, WS_OVERLAPPEDWINDOW, 100, 100, 500, 250, NULL, NULL, NULL, NULL);
	HDC hDC;
	HGLRC hRC;

	EnableOpenGL(hWnd, &hDC, &hRC);

	UserSettings::getInst().loadSettings("settings.ini");

	initGame();
	
	std::thread logicThread = std::thread(logicCycle);

	MSG msg;
	GetMessage(&msg, nullptr, 0, 0);
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (UserSettings::getInst().getGraphicsSettings().vSync == 0 &&
				wait(UserSettings::getInst().getGraphicsSettings().fps) == 0)
				continue;

			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			glLoadIdentity();
			
			Display::getInst().run(hWnd, hDC, hRC);

			SwapBuffers(hDC); // Меняем буффер
		}
	}

	logicThread.detach();

	gameDestructor();

	DisableOpenGL(hWnd, hDC, hRC);

	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };
	
	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	Events::getInst().run(hWnd, msg, wp, lp);

	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);

		LONG w = rect.right - rect.left;
		LONG h = rect.bottom - rect.top;
		glViewport(0, 0, w, h);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
		break;
	}
}

