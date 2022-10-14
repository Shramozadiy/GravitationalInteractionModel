#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include "Display.h"
#include "VectorP.h"
#include "StandardDisplayFunctions.h"

class Planet
{

private:
	VectorP coord_;
	VectorP vel_;
	VectorP acc_;

	double mass_ = 0;
	double radius_ = 0;

public:

	Planet(const VectorP& coord, const VectorP& vel, const VectorP& acc, double mass, double radius)
	{
		coord_ = coord;
		vel_ = vel;
		acc_ = acc;
		mass_ = mass;
		radius_ = radius;
	}

	void draw()
	{
		auto drawFunc = [this](HWND hWnd, HDC hDC, HGLRC hRC)
		{
			displayCircle(coord_.X(), coord_.Y(), radius_);
		};

		Display::getInst().add(drawFunc);
	}

	VectorP Coord()
	{
		return coord_;
	}

	VectorP Vel()
	{
		return vel_;
	}

	VectorP Acc()
	{
		return acc_;
	}

	double Radius()
	{
		return radius_;
	}

	double Mass()
	{
		return mass_;
	}

	void setCoord(const VectorP& coord)
	{
		coord_ = coord;
	}

	void setVel(const VectorP& vel)
	{
		vel_ = vel;
	}

	void setAcc(const VectorP& acc)
	{
		acc_ = acc;
	}

	void setRadius(double radius)
	{
		radius_ = radius;
	}

	void setMass(double mass)
	{
		mass_ = mass;
	}
};

