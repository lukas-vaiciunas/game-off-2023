#pragma once

#include "PartitionCell.h"

template<typename T, typename Container>
class Partition
{
public:
	Partition(
		const sf::Vector2u &gridSize,
		const sf::Vector2u &cellSize);

	void add(T *object);
	void remove(T *object);

	Container getObjectsNear(const sf::Vector2u &cellPosition) const;
	sf::Vector2u getCellPosition(const Coordinate &coordinate) const;
private:
	std::vector<std::vector<PartitionCell<T, Container>>> cells_;

	sf::Vector2u gridSize_;
	sf::Vector2u cellSize_;
};

template<typename T, typename Container>
Partition<T, Container>::Partition(
	const sf::Vector2u &gridSize,
	const sf::Vector2u &cellSize)
	:
	cells_(
		gridSize.y,
		std::vector<PartitionCell<T, Container>>(
			gridSize.x,
			PartitionCell<T, Container>())),
	gridSize_(gridSize),
	cellSize_(cellSize)
{}

template<typename T, typename Container>
void Partition<T, Container>::add(T *object)
{
	const sf::Vector2u cellPosition(
		std::move(
			this->getCellPosition(
				object->getCoordinate())));

	cells_[cellPosition.y][cellPosition.x].add(object);
}

template<typename T, typename Container>
void Partition<T, Container>::remove(T *object)
{
	const sf::Vector2u cellPosition(
		std::move(
			this->getCellPosition(
				object->getCoordinate())));

	cells_[cellPosition.y][cellPosition.x].remove(object);
}

template<typename T, typename Container>
Container Partition<T, Container>::getObjectsNear(const sf::Vector2u &cellPosition) const
{
	const std::vector<sf::Vector2i> offsets(
		{
			sf::Vector2i(-1, -1),
			sf::Vector2i(0, -1),
			sf::Vector2i(1, -1),
			sf::Vector2i(-1, 0),
			sf::Vector2i(0, 0),
			sf::Vector2i(1, 0),
			sf::Vector2i(-1, 1),
			sf::Vector2i(0, 1),
			sf::Vector2i(1, 1)
		});

	Container objects;

	for (const sf::Vector2i &offset : offsets)
	{
		const sf::Vector2u currentCellPosition(
			cellPosition.x + offset.x,
			cellPosition.y + offset.y);

		if (currentCellPosition.x >= gridSize_.x
			|| currentCellPosition.y >= gridSize_.y)
		{
			continue;
		}

		const Container &cellObjects = cells_[currentCellPosition.y][currentCellPosition.x].getObjects();

		objects.insert(
			cellObjects.begin(),
			cellObjects.end());

		/*for (auto it = cellObjects.begin(); it != cellObjects.end(); ++it)
		{
			objects.emplace(
				it->first,
				it->second);
		}*/
	}
	
	return objects;
}

template<typename T, typename Container>
sf::Vector2u Partition<T, Container>::getCellPosition(const Coordinate &coordinate) const
{
	const sf::Vector2u &mapCoordinate = coordinate.getPosition();

	return sf::Vector2u(
		mapCoordinate.x / cellSize_.x,
		mapCoordinate.y / cellSize_.y);
}