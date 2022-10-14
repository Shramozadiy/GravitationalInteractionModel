#pragma once

#include "Point.h"

template <typename Type>
class Ñircle
{
	Point<Type> center_;
	Type radius_;

public:

	Ñircle(Point<Type> center, Type radius);

};

template<typename Type>
inline Ñircle<Type>::Ñircle(Point<Type> center, Type radius)
{
	center_ = center;
	radius_ = radius;
}

