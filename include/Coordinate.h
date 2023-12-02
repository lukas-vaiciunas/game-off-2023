#pragma once

#include <SFML/System/Vector2.hpp>
#include <functional>

class Coordinate
{
public:
	Coordinate(const sf::Vector2u &position);

	uint64_t operator()(const Coordinate &coordinate) const;
	bool operator==(const Coordinate &other) const;
	bool operator<(const Coordinate &other) const;

	const sf::Vector2u &getPosition() const;
private:
	sf::Vector2u position_;
};

namespace std
{
	template<> struct hash<Coordinate>
	{
		uint64_t operator()(const Coordinate &coordinate) const;
	};
}