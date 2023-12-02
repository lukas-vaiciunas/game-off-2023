#pragma once

class Map;

#include <SFML/System/Vector2.hpp>
#include <stack>

namespace PathFinder
{
	std::stack<sf::Vector2u> findPath(
		const sf::Vector2u &from,
		const sf::Vector2u &to,
		const Map &map);

	float getManhattanDistance(
		const sf::Vector2u &from,
		const sf::Vector2u &to);

	float getEuclideanDistance(
		const sf::Vector2u &from,
		const sf::Vector2u &to);
}