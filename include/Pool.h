#pragma once

#include <vector>

template<typename T>
class Pool
{
public:
	typedef uint16_t Size;

	Pool(Size capacity);

	virtual ~Pool();

	typename std::vector<T *>::iterator begin();
	typename std::vector<T *>::iterator end();

	typename std::vector<T *>::const_iterator begin() const;
	typename std::vector<T *>::const_iterator end() const;
protected:
	std::vector<T *> objects_;
	Size capacity_;
	Size numLive_;

	void add_(T *object);
	void remove_(Size index);

	bool isFull_() const;
};

template<typename T>
Pool<T>::Pool(Size capacity) :
	objects_(capacity, nullptr),
	capacity_(capacity),
	numLive_(0)
{}

template<typename T>
Pool<T>::~Pool()
{
	for (Size i = 0; i < numLive_; ++i)
	{
		delete objects_[i];
	}
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::begin()
{
	return objects_.begin();
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::end()
{
	return objects_.begin() + numLive_;
}

template<typename T>
typename std::vector<T *>::const_iterator Pool<T>::begin() const
{
	return objects_.begin();
}

template<typename T>
typename std::vector<T *>::const_iterator Pool<T>::end() const
{
	return objects_.begin() + numLive_;
}

template<typename T>
void Pool<T>::add_(T *object)
{
	objects_[numLive_++] = object;
}

template<typename T>
void Pool<T>::remove_(Size index)
{
	delete objects_[index];
	objects_[index] = objects_[--numLive_];
	objects_[numLive_] = nullptr;
}

template<typename T>
bool Pool<T>::isFull_() const
{
	return numLive_ == capacity_;
}