#include "PathFinder.h"
#include "Map.h"
#include <queue>
#include <unordered_map>

namespace PathFinder
{
	namespace
	{
		struct Node
		{
			Node *parent = nullptr;
			sf::Vector2u coordinate = sf::Vector2u(0, 0);
			float gCost = 0.0f;
			float hCost = 0.0f;
			float fCost = 0.0f;
		};

		struct CompareNode
		{
			bool operator()(Node *lhs, const Node *rhs)
			{
				return lhs->fCost > rhs->fCost;
			}
		};

		struct HashVector
		{
			size_t operator()(const sf::Vector2u &vector) const
			{
				// TODO replace with map width
				return vector.x + vector.y * static_cast<size_t>(Constants::Map::width);
			}
		};

		typedef std::priority_queue<Node *, std::vector<Node *>, CompareNode> PriorityQueue;
		typedef std::unordered_map<sf::Vector2u, Node *, HashVector> UnorderedMap;

		void findPathHelper(
			const sf::Vector2u &coordinate,
			float gCost,
			float hCost,
			Node *current,
			PriorityQueue &queue,
			UnorderedMap &visited)
		{
			auto it = visited.find(coordinate);

			if (it != visited.end())
			{
				if (gCost < it->second->gCost)
				{
					it->second->parent = current;
					it->second->gCost = gCost;
					it->second->fCost = gCost + it->second->hCost;
				}
			}
			else
			{
				Node *next = new Node();
				next->parent = current;
				next->coordinate = coordinate;
				next->gCost = gCost;
				next->hCost = hCost;
				next->fCost = gCost + hCost;

				queue.emplace(next);
				visited.emplace(coordinate, next);
			}
		}
	}
	
	std::stack<sf::Vector2u> findPath(
		const sf::Vector2u &from,
		const sf::Vector2u &to,
		const Map &map)
	{
		if (from == to)
		{
			return {};
		}

		typedef sf::Vector2i Offset;

		const std::vector<Offset> offsets
		{
			sf::Vector2i(-1, 0),
			sf::Vector2i(0, -1),
			sf::Vector2i(1, 0),
			sf::Vector2i(0, 1)
		};

		const std::vector<Offset> diagonalOffsets
		{
			sf::Vector2i(-1, -1),
			sf::Vector2i(1, -1),
			sf::Vector2i(1, 1),
			sf::Vector2i(-1, 1)
		};

		const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = map.getVisibleResourceNodes();
		const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = map.getVisibleCamperEnemies();

		PriorityQueue queue;
		UnorderedMap visited;

		Node *source = new Node();
		source->parent = nullptr;
		source->coordinate = from;
		source->gCost = 0.0f;
		source->hCost = getManhattanDistance(from, to);
		source->fCost = source->gCost + source->hCost;
		
		queue.emplace(source);
		visited.emplace(source->coordinate, source);

		while (!queue.empty())
		{
			Node *current = queue.top();
			queue.pop();

			if (current->coordinate == to)
			{
				std::stack<sf::Vector2u> path;

				while (current->parent != nullptr)
				{
					path.emplace(current->coordinate);

					current = current->parent;
				}

				for (auto it = visited.begin(); it != visited.end(); ++it)
				{
					delete it->second;
				}

				return path;
			}

			for (const Offset &offset : offsets)
			{
				const sf::Vector2u coordinate(
					current->coordinate.x + offset.x,
					current->coordinate.y + offset.y);

				if (visibleResourceNodes.find(Coordinate(coordinate)) != visibleResourceNodes.end()
					|| visibleCamperEnemies.find(Coordinate(coordinate)) != visibleCamperEnemies.end())
				{
					continue;
				}

				findPathHelper(
					coordinate,
					current->gCost + 1.0f,
					getManhattanDistance(coordinate, to),
					current,
					queue,
					visited);
			}

			for (const Offset &offset : diagonalOffsets)
			{
				const sf::Vector2u coordinate(
					current->coordinate.x + offset.x,
					current->coordinate.y + offset.y);

				if (visibleResourceNodes.find(Coordinate(coordinate)) != visibleResourceNodes.end()
					|| visibleResourceNodes.find(Coordinate(sf::Vector2u(current->coordinate.x + offset.x, current->coordinate.y))) != visibleResourceNodes.end()
					|| visibleResourceNodes.find(Coordinate(sf::Vector2u(current->coordinate.x, current->coordinate.y + offset.y))) != visibleResourceNodes.end())
				{
					continue;
				}

				findPathHelper(
					coordinate,
					current->gCost + 1.4f,
					getManhattanDistance(coordinate, to),
					current,
					queue,
					visited);
			}
		}

		return {};
	}

	float getManhattanDistance(
		const sf::Vector2u &from,
		const sf::Vector2u &to)
	{
		return fabsf(static_cast<float>(to.x) - from.x) + fabsf(static_cast<float>(to.y) - from.y);
	}

	float getEuclideanDistance(
		const sf::Vector2u &from,
		const sf::Vector2u &to)
	{
		sf::Vector2f delta(sf::Vector2f(to) - sf::Vector2f(from));

		return sqrtf(delta.x * delta.x + delta.y * delta.y);
	}
}