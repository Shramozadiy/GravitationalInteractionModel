#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include "Camera.h"
#include "Resource.h"
#include "MyGeometry/MyGeometry.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename Type>
class Camera;

template <typename Type>
Type degreesToRadians(Type alpha)
{
	double pi = 3.1415926535;
	Type newAlpha = alpha * pi / 180.0;
	return newAlpha;
}

template <typename Type>
void rotationRelativeToPoint(Point<Type>& p, const Point<Type>& p0, Type alpha)
{
	alpha = degreesToRadians(alpha);

	Type x = (p.X() - p0.X()) * cos(alpha) - (p.Y() - p0.Y()) * sin(alpha) + p0.X();
	Type y = (p.X() - p0.X()) * sin(alpha) + (p.Y() - p0.Y()) * cos(alpha) + p0.Y();

	p = { x, y };
}

template<typename Type>
void cursorToCamera(Type& xCursor, Type& yCursor, const Camera<Type>& camera)
{
	HWND hWnd = FindWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);

	RECT rect;
	GetClientRect(hWnd, &rect);
	Type w = rect.right - rect.left;
	Type h = rect.bottom - rect.top;

	Type x = p.x;
	Type y = h - p.y;

	x = 2.0 * x / w - 1.0;
	y = 2.0 * y / h - 1.0;

	Point<Type> cursor = { x / (camera.getScale() * h / w) , y / camera.getScale() };
	rotationRelativeToPoint(cursor, { 0.0, 0.0 }, -camera.getPosition().Alpha());

	xCursor = cursor.X() + camera.getPosition().X();
	yCursor = cursor.Y() + camera.getPosition().Y();
}

template<typename Type>
void cursorToCamera(Type& xCursor, Type& yCursor, const Position<Type>& position, Type scale)
{
	HWND hWnd = FindWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);

	RECT rect;
	GetClientRect(hWnd, &rect);
	Type w = rect.right - rect.left;
	Type h = rect.bottom - rect.top;

	Type x = p.x;
	Type y = h - p.y;

	x = 2.0 * x / w - 1.0;
	y = 2.0 * y / h - 1.0;

	Point<Type> cursor = { x / (scale * h / w), y / scale };
	rotationRelativeToPoint(cursor, { 0.0, 0.0 }, -position.Alpha());

	xCursor = cursor.X() + position.X();
	yCursor = cursor.Y() + position.Y();
}
