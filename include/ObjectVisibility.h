#pragma once

#include "Partition.h"
#include "Constants.h"

template<typename T, typename Container>
class ObjectVisibility
{
public:
	ObjectVisibility();

	void update(const sf::Vector2u &coordinate);
	void refresh();

	void add(T *object);
	void removeAndDelete(T *object);

	Partition<T, Container> &getPartition();

	const Container &getVisibleObjects() const;
private:
	Partition<T, Container> partition_;
	Container visibleObjects_;
	sf::Vector2u partitionCellPosition_;
};

template<typename T, typename Container>
ObjectVisibility<T, Container>::ObjectVisibility()
	:
	partition_(
		sf::Vector2u(
			static_cast<uint32_t>(std::ceilf(static_cast<float>(Constants::Map::width) / Constants::Visibility::cellSize)),
			static_cast<uint32_t>(std::ceilf(static_cast<float>(Constants::Map::height) / Constants::Visibility::cellSize))),
		sf::Vector2u(
			Constants::Visibility::cellSize,
			Constants::Visibility::cellSize)),
	visibleObjects_(),
	partitionCellPosition_(0, 0)
{}

template<typename T, typename Container>
void ObjectVisibility<T, Container>::update(const sf::Vector2u &coordinate)
{
	const sf::Vector2u partitionCellPosition(
		std::move(
			partition_.getCellPosition(
				coordinate)));

	if (partitionCellPosition_ == partitionCellPosition)
	{
		return;
	}

	partitionCellPosition_ = partitionCellPosition;

	this->refresh();
}

template<typename T, typename Container>
void ObjectVisibility<T, Container>::refresh()
{
	visibleObjects_ = std::move(
		partition_.getObjectsNear(
			partitionCellPosition_));
}

template<typename T, typename Container>
void ObjectVisibility<T, Container>::add(T *object)
{
	partition_.add(object);
}

template<typename T, typename Container>
void ObjectVisibility<T, Container>::removeAndDelete(T *object)
{
	partition_.remove(object);

	delete object;
}

template<typename T, typename Container>
Partition<T, Container> &ObjectVisibility<T, Container>::getPartition()
{
	return partition_;
}

template<typename T, typename Container>
const Container &ObjectVisibility<T, Container>::getVisibleObjects() const
{
	return visibleObjects_;
}