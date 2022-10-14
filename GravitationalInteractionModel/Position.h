#pragma once

template <typename Type>
class Position
{
	Type x_ = 0;
	Type y_ = 0;
	Type alpha_ = 0;

public:

	Position();
	Position(Type x, Type y, Type alpha);
	Position(const Position&);

	Type X() const;
	Type Y() const;
	Type Alpha() const;

	void SetPosition(Type x, Type y, Type alpha);

};

template<typename Type>
inline Position<Type>::Position()
{
}

template<typename Type>
inline Position<Type>::Position(Type x, Type y, Type alpha)
{
	x_ = x;
	y_ = y;
	alpha_ = alpha;
}

template<typename Type>
inline Position<Type>::Position(const Position& pos)
{
	x_ = pos.X();
	y_ = pos.Y();
	alpha_ = pos.Alpha();
}

template<typename Type>
inline Type Position<Type>::X() const
{
	return x_;
}

template<typename Type>
inline Type Position<Type>::Y() const
{
	return y_;
}

template<typename Type>
inline Type Position<Type>::Alpha() const
{
	return alpha_;
}

template<typename Type>
inline void Position<Type>::SetPosition(Type x, Type y, Type alpha)
{
	x_ = x;
	y_ = y;
	alpha_ = alpha;
}
