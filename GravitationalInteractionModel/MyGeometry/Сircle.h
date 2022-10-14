#pragma once

#include "Point.h"

template <typename Type>
class �ircle
{
	Point<Type> center_;
	Type radius_;

public:

	�ircle(Point<Type> center, Type radius);

};

template<typename Type>
inline �ircle<Type>::�ircle(Point<Type> center, Type radius)
{
	center_ = center;
	radius_ = radius;
}

