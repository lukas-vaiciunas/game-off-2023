#include "Coordinate.h"
#include "Constants.h"

Coordinate::Coordinate(const sf::Vector2u &position) :
	position_(position)
{}

uint64_t Coordinate::operator()(const Coordinate &coordinate) const
{
	return position_.x + position_.y * static_cast<uint64_t>(Constants::Map::width);
}

bool Coordinate::operator==(const Coordinate &other) const
{
	return position_ == other.position_;
}

bool Coordinate::operator<(const Coordinate &other) const
{
	return position_.y < other.position_.y;
}

const sf::Vector2u &Coordinate::getPosition() const
{
	return position_;
}

namespace std
{
	uint64_t hash<Coordinate>::operator()(const Coordinate &coordinate) const
	{
		return coordinate(coordinate);
	}
}