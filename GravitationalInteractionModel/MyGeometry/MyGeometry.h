#pragma once

#include "Point.h"
#include "Segment.h"
#include "StraightLine.h"
#include "Ñircle.h"

template<typename Type>
bool isIntersecting(const Segment<Type>& seg1, const Segment<Type>& seg2);

template<typename Type>
bool isIntersecting(const Segment<Type>& seg1, const StraightLine<Type>& line);

template<typename Type>
bool isIntersecting(const StraightLine<Type>& line1, const StraightLine<Type>& line2);

template <typename Type>
Point<Type> intersectionPoint(const Segment<Type>& seg1, const Segment<Type>& seg2);

template <typename Type>
Point<Type> intersectionPoint(const Segment<Type>& segment, const StraightLine<Type>& line);

template <typename Type>
Point<Type> intersectionPoint(const StraightLine<Type>& line1, const StraightLine<Type>& line2);


template<typename Type>
inline bool isIntersecting(const Segment<Type>& seg1, const Segment<Type>& seg2)
{
	Type x1 = seg1.P1().X();
	Type x2 = seg1.P2().X();
	Type x3 = seg2.P1().X();
	Type x4 = seg2.P2().X();
	Type y1 = seg1.P1().Y();
	Type y2 = seg1.P2().Y();
	Type y3 = seg2.P1().Y();
	Type y4 = seg2.P2().Y();

	Type v1 = x2 - x1;
	Type v2 = x4 - x3;
	Type w1 = y2 - y1;
	Type w2 = y4 - y3;

	if ((v1 - v2 * w1) == 0 && (v2 - v1 * w2) == 0)
		return 0;

	Type t1 = (v2 * (y1 - y3) + w2 * (x2 - x1)) / (v1 - v2 * w1);
	Type t2 = (v1 * (y3 - y1) + w1 * (x1 - x2)) / (v2 - v1 * w2);

	if (t1 >= 0 && t1 <= 1 && t2 >= 0 && t2 <= 1)
		return 1;

	return 0;
}

template<typename Type>
inline bool isIntersecting(const Segment<Type>& segment, const StraightLine<Type>& line)
{
	Type x1 = segment.P1().X();
	Type y1 = segment.P1().Y();
	Type x2 = segment.P2().X();
	Type y2 = segment.P2().Y();

	Type k = line.K();
	Type b = line.B();

	Type delta_y1 = y1 - k * x1 - b;
	Type delta_y2 = y2 - k * x2 - b;

	if (delta_y1 * delta_y2 <= 0)
		return 1;
	return 0;
}

template<typename Type>
inline bool isIntersecting(const StraightLine<Type>& line1, const StraightLine<Type>& line2)
{
	Type k1 = line1.K();
	Type k2 = line2.K();

	if (k1 == k2)
		return 0;

	return 1;
}

template<typename Type>
inline Point<Type> intersectionPoint(const Segment<Type>& seg1, const Segment<Type>& seg2)
{
	Point<Type> point;

	StraightLine<Type> line1(seg1.P1(), seg1.P2());
	StraightLine<Type> line2(seg2.P1(), seg2.P2());

	point = intersectionPoint(line1, line2);

	return point;
}

template<typename Type>
inline Point<Type> intersectionPoint(const Segment<Type>& segment, const StraightLine<Type>& line)
{
	Point<Type> point;

	StraightLine<Type> line2(segment.P1(), segment.P2());

	point = intersectionPoint(line, line2);

	return point;
}

template<typename Type>
inline Point<Type> intersectionPoint(const StraightLine<Type>& line1, const StraightLine<Type>& line2)
{
	Point<Type> point;

	Type x1 = line1.P1().X();
	Type y1 = line1.P1().Y();
	Type x2 = line1.P2().X();
	Type y2 = line1.P2().Y();

	Type x3 = line2.P1().X();
	Type y3 = line2.P1().Y();
	Type x4 = line2.P2().X();
	Type y4 = line2.P2().Y();

	Type a1 = y2 - y1;
	Type b1 = x2 - x1;
	Type c1 = y2 * x1 - x2 * y1;

	Type a2 = y4 - y3;
	Type b2 = x4 - x3;
	Type c2 = y4 * x3 - x4 * y3;

	if (b2 * a1 - b1 * a2 == 0)
	{
		point = { 0, 0 };
		return point;
	}

	Type y = (c1 * a2 - c2 * a1) / (b2 * a1 - b1 * a2);
	Type x;

	if (a1 != 0)
		x = (b1 * y + c1) / a1;
	else 
		x = (b2 * y + c2) / a2;

	point = { x, y };

	return point;
}
