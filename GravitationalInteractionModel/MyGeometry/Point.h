#pragma once

#include <math.h>

template <typename Type>
class Point
{
	Type x_;
	Type y_;

public:

	Point();
	Point(Type x, Type y);
	Point(const Point& obj);


	Type X() const;
	Type Y() const;

	void setCoordinates(Type x, Type y);

	static Type scalarProduct(Point p1, Point p2);

};

template<typename Type>
inline Point<Type>::Point()
{
	x_ = 0;
	y_ = 0;
}

template<typename Type>
inline Point<Type>::Point(Type x, Type y)
{
	x_ = x;
	y_ = y;
}

template<typename Type>
inline Point<Type>::Point(const Point& obj)
{
	this->x_ = obj.x_;
	this->y_ = obj.y_;
}

template<typename Type>
inline Type Point<Type>::X() const
{
	return x_;
}

template<typename Type>
inline Type Point<Type>::Y() const
{
	return y_;
}

template<typename Type>
inline void Point<Type>::setCoordinates(Type x, Type y)
{
	x_ = x;
	y_ = y;
}


template<typename Type>
inline Type Point<Type>::scalarProduct(Point p1, Point p2)
{
	Type result = p1.X() * p2.X() + p1.Y() + p2.Y();

	return result;
}