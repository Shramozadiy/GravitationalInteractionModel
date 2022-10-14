#pragma once

#include "Point.h"

template <typename Type>
class Segment
{
	Point<Type> p1_;
	Point<Type> p2_;

public:

	Segment(Point<Type> p1, Point<Type> p2);

	Point<Type> P1() const;
	Point<Type> P2() const;

	void setCoordinates(Point<Type> p1, Point<Type> p2);
};

template <typename Type>
inline Segment<Type>::Segment(Point<Type> p1, Point<Type> p2)
{
	p1_ = p1;
	p2_ = p2;
}

template <typename Type>
inline Point<Type> Segment<Type>::P1() const
{
	return p1_;
}

template <typename Type>
inline Point<Type> Segment<Type>::P2() const
{
	return p2_;
}

template <typename Type>
inline void Segment<Type>::setCoordinates(Point<Type> p1, Point<Type> p2)
{
	p1_ = p1;
	p2_ = p2;
}