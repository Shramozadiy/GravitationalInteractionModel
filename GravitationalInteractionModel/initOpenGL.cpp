#include "initOpenGL.h"


void set_vsync(bool enabled) // true -- VSync включен, false -- выключен
{
	PFNWGLSWAPINTERVALEXTPROC wglSwapInterval = NULL;

	wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapInterval) wglSwapInterval(enabled ? 1 : 0);
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
	PIXELFORMATDESCRIPTOR pfd;

	int iFormat;

	/* get the device context (DC) */
	*hDC = GetDC(hwnd);

	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hDC, &pfd);

	SetPixelFormat(*hDC, iFormat, &pfd);

	/* create and enable the render context (RC) */
	*hRC = wglCreateContext(*hDC);

	wglMakeCurrent(*hDC, *hRC);

	set_vsync(1);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hwnd, hDC);
}

bool wait(int fps)
{
	static auto start = std::chrono::steady_clock::now();
	static auto end = std::chrono::steady_clock::now();

	end = std::chrono::steady_clock::now();
	static auto wait_time = std::chrono::microseconds((int)(1000000.0 / fps));
	if (wait_time > end - start)
		return 0;
	else
	{
		start = std::chrono::steady_clock::now();
		return 1;
	}
}