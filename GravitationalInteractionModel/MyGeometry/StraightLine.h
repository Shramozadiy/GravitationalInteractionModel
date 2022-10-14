#pragma once

#include "Point.h"
#include "Segment.h"


template <typename Type>
class StraightLine
{
	Point<Type> p1_;
	Point<Type> p2_;

	Type k_;
	Type b_;

public:

	StraightLine(Type k, Type b);
	StraightLine(Point<Type> p1, Point<Type> p2);

	Type Y(Type x) const;
	Type X(Type y) const;

	Type K() const;
	Type B() const;

	Point<Type> P1() const;
	Point<Type> P2() const;
};

template<typename Type>
StraightLine<Type>::StraightLine(Type k, Type b)
{
	k_ = k;
	b_ = b;

	p1_ = {0, b};
	p2_ = {2, k * 2 + b};
}

template<typename Type>
StraightLine<Type>::StraightLine(Point<Type> p1, Point<Type> p2)
{
	p1_ = p1;
	p2_ = p2;

	k_ = (p2.Y() - p1.Y()) / (p2.X() - p1.X());
	b_ = (p2.X() * p1.Y() - p1.X() * p2.Y()) / (p2.X() - p1.X());
}


template<typename Type>
Type StraightLine<Type>::Y(Type x) const
{
	Type x1 = p1_.X();
	Type x2 = p2_.X();
	Type y1 = p1_.Y();
	Type y2 = p2_.Y();

	if (y1 == y2)
		return y1;

	Type y = (x - x2) * (y2 - y1) / (x2 - x1) + y2;
	return y;
}

template<typename Type>
Type StraightLine<Type>::X(Type y) const
{
	Type x1 = p1_.X();
	Type x2 = p2_.X();
	Type y1 = p1_.Y();
	Type y2 = p2_.Y();

	if (x1 == x2)
		return x1;

	Type x = (y - y2) * (x2 - x1) / (y2 - y1) + x2;
	return x;
}

template<typename Type>
Type StraightLine<Type>::K() const
{
	return k_;
}

template<typename Type>
Type StraightLine<Type>::B() const
{
	return b_;
}

template<typename Type>
Point<Type> StraightLine<Type>::P1() const
{
	return p1_;
}

template<typename Type>
Point<Type> StraightLine<Type>::P2() const
{
	return p2_;
}

//template <typename Type>
//class StraightLine
//{
//	Type k_;
//	Type b_;
//
//public:
//
//	StraightLine(Type k, Type b);
//
//	StraightLine(Point<Type> p1, Point<Type> p2);
//
//	Type Y(Type x) const;
//	Type X(Type y) const;
//
//	Type K() const;
//	Type B() const;
//
//};
//
//template<typename Type>
//StraightLine<Type>::StraightLine(Type k, Type b)
//{
//	k_ = k;
//	b_ = b;
//}
//
//template<typename Type>
//StraightLine<Type>::StraightLine(Point<Type> p1, Point<Type> p2)
//{
//	k_ = (p2.Y() - p1.Y()) / (p2.X() - p1.X());
//	b_ = (p2.X() * p1.Y() - p1.X() * p2.Y()) / (p2.X() - p1.X());
//}
//
//template<typename Type>
//Type StraightLine<Type>::Y(Type x) const
//{
//	Type y = k_ * x + b_;
//	return y;
//}
//
//template<typename Type>
//Type StraightLine<Type>::X(Type y) const
//{
//	Type x = (y - b_) / k_;
//	return Type();
//}
//
//template<typename Type>
//Type StraightLine<Type>::K() const
//{
//	return k_;
//}
//
//template<typename Type>
//Type StraightLine<Type>::B() const
//{
//	return b_;
//}
