#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include <thread>

typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC) (int interval);
void set_vsync(bool enabled); // true -- VSync включен, false -- выключен
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC);
bool wait(int fps);