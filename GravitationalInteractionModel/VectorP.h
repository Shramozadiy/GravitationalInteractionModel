#pragma once

#include <cmath>

class VectorP
{
private:

	double x_ = 0;
	double y_ = 0;
	double z_ = 0;


public:

	double X()
	{
		return x_;
	}

	double Y()
	{
		return y_;
	}

	double Z()
	{
		return z_;
	}

	VectorP(double x = 0, double y = 0, double z = 0)
	{
		x_ = x;
		y_ = y;
		z_ = z;
	}

	VectorP(const VectorP& v)
	{
		x_ = v.x_;
		y_ = v.y_;
		z_ = v.z_;
	}

	VectorP operator+(const VectorP& v)
	{
		double x = x_ + v.x_;
		double y = y_ + v.y_;
		double z = z_ + v.z_;
		VectorP newV(x, y, z);
		return newV;
	}

	VectorP operator-(const VectorP& v)
	{
		double x = x_ - v.x_;
		double y = y_ - v.y_;
		double z = z_ - v.z_;
		VectorP newV(x, y, z);
		return newV;
	}

	VectorP operator*(const double a)
	{
		double x = x_ * a;
		double y = y_ * a;
		double z = z_ * a;
		VectorP newV(x, y, z);
		return newV;
	}

	double distance2(const VectorP& v)
	{
		double d2 = (x_ - v.x_) * (x_ - v.x_) + (y_ - v.y_) * (y_ - v.y_) + (z_ - v.z_) * (z_ - v.z_);

		return d2;
	}

	VectorP operator/(const double a)
	{
		double x = x_ / a;
		double y = y_ / a;
		double z = z_ / a;
		VectorP newV(x, y, z);
		return newV;
	}

	VectorP Abs()
	{
		double x = abs(x_);
		double y = abs(y_);
		double z = abs(z_);
		VectorP newV(x, y, z);
		return newV;
	}
};

