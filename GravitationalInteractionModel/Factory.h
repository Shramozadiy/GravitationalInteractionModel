#pragma once


#include <vector>

template <typename Type>
class Factory
{
	Factory() {};
	Factory(const Factory&);
	Factory& operator=(Factory&) {};

	std::vector<Type> data_;
public:

	static Factory& getInst();

	void add(const Type& object);

	Type& operator[](int index);

	Type& begin();
	Type& end();

	size_t size();
};


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


template<typename Type>
inline Factory<Type>& Factory<Type>::getInst()
{
	static Factory instance;
	return instance;
}

template<typename Type>
inline void Factory<Type>::add(const Type& object)
{
	data_.push_back(object);
}

template<typename Type>
inline Type& Factory<Type>::operator[](int index)
{
	return data_[index];
}

template<typename Type>
inline Type& Factory<Type>::begin()
{
	return data_.begin();
}

template<typename Type>
inline Type& Factory<Type>::end()
{
	return data_.end();
}

template<typename Type>
inline size_t Factory<Type>::size()
{
	return data_.size();
}
