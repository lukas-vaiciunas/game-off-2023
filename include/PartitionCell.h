#pragma once

#include "Coordinate.h"

template<typename T, typename Container>
class PartitionCell
{
public:
	PartitionCell();

	~PartitionCell();

	void add(T *object);
	void remove(T *object);

	const Container &getObjects() const;
private:
	Container objects_;
};

template<typename T, typename Container>
PartitionCell<T, Container>::PartitionCell() :
	objects_()
{}

template<typename T, typename Container>
PartitionCell<T, Container>::~PartitionCell()
{
	for (auto it = objects_.begin(); it != objects_.end(); ++it)
	{
		delete it->second;
	}
}

template<typename T, typename Container>
void PartitionCell<T, Container>::add(T *object)
{
	objects_.emplace(
		object->getCoordinate(),
		object);
}

template<typename T, typename Container>
void PartitionCell<T, Container>::remove(T *object)
{
	auto iterators = objects_.equal_range(object->getCoordinate());

	for (auto it = iterators.first; it != iterators.second; ++it)
	{
		if (it->second == object)
		{
			objects_.erase(it);
			break;
		}
	}
}

template<typename T, typename Container>
const Container &PartitionCell<T, Container>::getObjects() const
{
	return objects_;
}