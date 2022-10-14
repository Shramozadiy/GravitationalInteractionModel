#pragma once

#include <Windows.h>
#include <gl/GL.h>

//#include "Cursor.h"
#include "Position.h"
#include "Factory.h"
#include "Resource.h"

#include "Cursor.h"


template <typename Type>
class Camera
{
	Position<Type> position_;
	Type scale_;
	Type deltaScale_;
	bool iActive_ = false;

public:

	Camera(const Position<Type>& position, Type scale, Type deltaScale);
	
	void enable();
	void disable();

	Position<Type> getPosition() const;
	Type getScale() const;

	void setPosition(const Position<Type>& position);

	void setDeltaScale(Type scale);
	void mouseWheel(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void mouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static void enable(int index);

	bool isActive();

	static Camera<Type>& getCurrentCamera();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




template<typename Type>
inline Camera<Type>::Camera(const Position<Type>& position, Type scale, Type deltaScale)
{
	position_ = position;
	scale_ = scale;
	deltaScale_ = deltaScale;
}

template<typename Type>
inline void Camera<Type>::enable()
{
	HWND hWnd = FindWindow(MAIN_WINDOW_CLASS_NAME, MAIN_WINDOW_NAME);
	RECT rect;
	GetClientRect(hWnd, &rect);
	Type w = rect.right - rect.left;
	Type h = rect.bottom - rect.top;

	glLoadIdentity();
	glScaled((double)scale_ * h / w, (double)scale_, 1.0);
	glRotated((double)position_.Alpha(), 0.0, 0.0, 1.0);
	glTranslated(-(double)position_.X(), -(double)position_.Y(), 0.0);
	
	Factory<Camera<Type>>& cameras = Factory<Camera<Type>>::getInst();
	for (int i = 0; i < cameras.size(); i++)
		cameras[i].disable();

	iActive_ = true;
}

template<typename Type>
inline void Camera<Type>::disable()
{
	iActive_ = false;
	//glLoadIdentity();
}

template<typename Type>
inline Position<Type> Camera<Type>::getPosition() const
{
	return position_;
}

template<typename Type>
inline void Camera<Type>::setPosition(const Position<Type>& position)
{
	position_ = position;
}

template<typename Type>
inline Type Camera<Type>::getScale() const
{
	return scale_;
}

template<typename Type>
inline void Camera<Type>::setDeltaScale(Type scale)
{
	deltaScale_ = scale;
}

template<typename Type>
inline void Camera<Type>::mouseWheel(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MOUSEWHEEL)
	{
		static double wheelDelta = 0;
		wheelDelta += GET_WHEEL_DELTA_WPARAM(wParam);

		for (; wheelDelta >= WHEEL_DELTA; wheelDelta -= WHEEL_DELTA)
		{
			scale_ += deltaScale_;
		}
		for (; wheelDelta <= 0; wheelDelta += WHEEL_DELTA)
		{
			scale_ -= deltaScale_;
		}
	}
}



template<typename Type>
inline void Camera<Type>::mouseMove(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool iLButtonDown = 0;
	static Position<Type> previousPosition = getPosition();
	static Type xPrevCursor = 0;
	static Type yPrevCursor = 0;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		iLButtonDown = 1;
		previousPosition = getPosition();
		cursorToCamera(xPrevCursor, yPrevCursor, previousPosition, scale_);
		break;
	case WM_LBUTTONUP:
		iLButtonDown = 0;
		break;
	case WM_MOUSEMOVE:
		if (iLButtonDown == 1)
		{
			Type xCursor, yCursor;
			cursorToCamera(xCursor, yCursor, previousPosition, scale_);
			position_ = { previousPosition.X() + xPrevCursor - xCursor, previousPosition.Y() + yPrevCursor - yCursor, position_.Alpha()};
		}
		break;
	default:
		break;
	}
}



template<typename Type>
inline bool Camera<Type>::isActive()
{
	return iActive_;
}

template<typename Type>
inline void Camera<Type>::enable(int index)
{
	Factory<Camera<Type>>& cameras = Factory<Camera<Type>>::getInst();
	cameras[index].enable();
}

template<typename Type>
inline Camera<Type>& Camera<Type>::getCurrentCamera()
{
	Factory<Camera<Type>>& cameras = Factory<Camera<Type>>::getInst();
	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i].isActive())
			return cameras[i];
	}
	return cameras[0];
}
