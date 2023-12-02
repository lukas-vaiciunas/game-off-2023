#include "Map.h"
#include "CamperEnemyTemplate.h"
#include "Event.h"
#include "TextureData.h"
#include "PathFinder.h"
#include "Random.h"
#include "Constants.h"
#include <map>
#include <fstream>
#include <sstream>

Map::Map() :
	Listener({ EventType::CamperEnemyDeath }),
	tileVisibility_(),
	resourceNodeVisibility_(),
	camperEnemyVisibility_(),
	hunterEnemyPool_(100)
{
	this->initialize_();

	tileVisibility_.refresh();
	resourceNodeVisibility_.refresh();
	camperEnemyVisibility_.refresh();
}

void Map::onEvent(const Event &ev)
{
	camperEnemyVisibility_.removeAndDelete(
		static_cast<const EventCamperEnemyDeath &>(ev).getCamperEnemy());

	camperEnemyVisibility_.refresh();
}

void Map::update(float deltaTime, const sf::Vector2u &playerCoordinate)
{
	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = resourceNodeVisibility_.getVisibleObjects();
	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = camperEnemyVisibility_.getVisibleObjects();

	for (auto it = visibleCamperEnemies.begin(); it != visibleCamperEnemies.end(); ++it)
	{
		it->second->update(deltaTime);
		it->second->updateCombat(deltaTime, playerCoordinate, *this);
	}

	for (auto it = visibleResourceNodes.begin(); it != visibleResourceNodes.end(); ++it)
	{
		it->second->update(deltaTime);
	}

	hunterEnemyPool_.update(deltaTime);
	hunterEnemyPool_.updateCombat(deltaTime, playerCoordinate, *this);

	// TODO only do visibility checks when player moves

	this->updateVisibility(playerCoordinate);
}

void Map::updateVisibility(const sf::Vector2u &playerCoordinate)
{
	tileVisibility_.update(playerCoordinate);
	resourceNodeVisibility_.update(playerCoordinate);
	camperEnemyVisibility_.update(playerCoordinate);
}

std::vector<sf::Vector2u> Map::getNavigableAdjacents(
	const sf::Vector2u &coordinate) const
{
	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = resourceNodeVisibility_.getVisibleObjects();
	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = camperEnemyVisibility_.getVisibleObjects();

	std::vector<sf::Vector2u> navigableAdjacents;

	const std::vector<sf::Vector2i> offsets
	{
		sf::Vector2i(-1, 0),
		sf::Vector2i(0, -1),
		sf::Vector2i(1, 0),
		sf::Vector2i(0, 1)
	};

	for (const sf::Vector2i &offset : offsets)
	{
		sf::Vector2u adjacent(
			coordinate.x + offset.x,
			coordinate.y + offset.y);

		if (visibleResourceNodes.find(Coordinate(adjacent)) != visibleResourceNodes.end()
			|| visibleCamperEnemies.find(Coordinate(adjacent)) != visibleCamperEnemies.end())
		{
			continue;
		}

		navigableAdjacents.emplace_back(std::move(adjacent));
	}

	return navigableAdjacents;
}

const sf::Vector2u &Map::getClosestCoordinate(
	const sf::Vector2u &from,
	const std::vector<sf::Vector2u> &options) const
{
	size_t minIndex = 0;
	float minDistance = PathFinder::getEuclideanDistance(from, options[0]);

	for (size_t i = 1; i < options.size(); ++i)
	{
		float distance = PathFinder::getEuclideanDistance(from, options[i]);

		if (distance < minDistance)
		{
			minIndex = i;
			minDistance = distance;
		}
	}

	return options[minIndex];
}

const std::unordered_map<Coordinate, Tile *> &Map::getVisibleTiles() const
{
	return tileVisibility_.getVisibleObjects();
}

const std::unordered_map<Coordinate, ResourceNode *> &Map::getVisibleResourceNodes() const
{
	return resourceNodeVisibility_.getVisibleObjects();
}

const std::unordered_multimap<Coordinate, CamperEnemy *> &Map::getVisibleCamperEnemies() const
{
	return camperEnemyVisibility_.getVisibleObjects();
}

const HunterEnemyPool &Map::getHunterEnemyPool() const
{
	return hunterEnemyPool_;
}

/*void Map::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	const std::unordered_map<Coordinate, Tile *> &visibleTiles = tileVisibility_.getVisibleObjects();
	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = resourceNodeVisibility_.getVisibleObjects();
	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = camperEnemyVisibility_.getVisibleObjects();

	for (auto it = visibleTiles.begin(); it != visibleTiles.end(); ++it)
	{
		it->second->draw(target, states, offset, scale);
	}

	std::multimap<Coordinate, ResourceNode *> sortedResourceNodes;

	sortedResourceNodes.insert(visibleResourceNodes.begin(), visibleResourceNodes.end());

	for (auto it = sortedResourceNodes.begin(); it != sortedResourceNodes.end(); ++it)
	{
		it->second->draw(target, states, offset, scale);
	}

	for (auto it = visibleCamperEnemies.begin(); it != visibleCamperEnemies.end(); ++it)
	{
		it->second->draw(target, states, offset, scale);
	}

	hunterEnemyPool_.draw(target, states, offset, scale);
}*/

void Map::initialize_()
{
	const TextureData &textureData = TextureData::getInstance();
	const sf::Vector2u mapChunkSize(
		Constants::Map::width / Constants::Chunk::size,
		Constants::Map::height / Constants::Chunk::size);

	const sf::Vector2u spawnChunkCoordinate = mapChunkSize / 2U;

	std::mt19937 &engine = Random::getInstance().getEngine();
	std::uniform_int_distribution<TextureId> grassTileTextureIdDis(201, 202);
	std::uniform_int_distribution<TextureId> dirtTileTextureIdDis(211, 212);
	std::uniform_int_distribution<TextureId> gloomTileTextureIdDis(241, 242);

	std::vector<std::vector<ChunkBiome>> chunkBiomeMap(
		mapChunkSize.y,
		std::vector<ChunkBiome>(
			mapChunkSize.x,
			ChunkBiome::Grass));

	ChunkBiome currentChunkBiome = ChunkBiome::Gloom;

	for (uint32_t row = 4; row < mapChunkSize.y; row += 5)
	{
		for (uint32_t col = 4; col < mapChunkSize.x; col += 5)
		{
			const sf::Vector2u chunkCoordinate(col, row);

			if (chunkCoordinate != spawnChunkCoordinate)
			{
				this->spreadBiomeChunks_(
					chunkCoordinate,
					mapChunkSize,
					chunkBiomeMap,
					currentChunkBiome);
			}

			if (currentChunkBiome == ChunkBiome::Dirt)
			{
				currentChunkBiome = ChunkBiome::Gloom;
			}
			else if (currentChunkBiome == ChunkBiome::Gloom)
			{
				currentChunkBiome = ChunkBiome::Dirt;
			}
		}
	}

	std::unordered_set<Coordinate> freeGrassChunkCoordinates;
	std::unordered_set<Coordinate> freeDirtChunkCoordinates;
	std::unordered_set<Coordinate> freeGloomChunkCoordinates;

	for (uint32_t row = 0; row < mapChunkSize.y; ++row)
	{
		for (uint32_t col = 0; col < mapChunkSize.x; ++col)
		{
			const sf::Vector2u chunkCoordinate(col, row);

			switch (chunkBiomeMap[row][col])
			{
				case ChunkBiome::Grass:
					this->fillChunk_(
						chunkCoordinate,
						grassTileTextureIdDis,
						engine,
						textureData);
					if (chunkCoordinate != spawnChunkCoordinate)
					{
						freeGrassChunkCoordinates.emplace(chunkCoordinate);
					}
					break;
				case ChunkBiome::Dirt:
					this->fillChunkWithBorders(
						chunkCoordinate,
						ChunkBiome::Dirt,
						chunkBiomeMap,
						mapChunkSize,
						dirtTileTextureIdDis,
						engine,
						textureData,
						221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232);
					if (chunkCoordinate != spawnChunkCoordinate)
					{
						freeDirtChunkCoordinates.emplace(chunkCoordinate);
					}
					break;
				case ChunkBiome::Gloom:
					this->fillChunkWithBorders(
						chunkCoordinate,
						ChunkBiome::Gloom,
						chunkBiomeMap,
						mapChunkSize,
						gloomTileTextureIdDis,
						engine,
						textureData,
						251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262);
					if (chunkCoordinate != spawnChunkCoordinate)
					{
						freeGloomChunkCoordinates.emplace(chunkCoordinate);
					}
					break;
			}
		}
	}

	enum class NodeType : uint8_t
	{
		Resource,
		CamperEnemy
	};

	std::queue<std::pair<ItemId, uint64_t>> grassResourceQuota(
		{
			{ 501, freeGrassChunkCoordinates.size() / 6 },
			{ 502, freeGrassChunkCoordinates.size() / 6 },
			{ 601, freeGrassChunkCoordinates.size() / 6 },
			{ 602, freeGrassChunkCoordinates.size() / 6 }
		});

	std::pair<TextureId, uint64_t> grassCamperEnemyQuota(1, freeGrassChunkCoordinates.size() / 6);

	std::queue<std::pair<ItemId, uint64_t>> dirtResourceQuota(
		{
			{ 503, freeDirtChunkCoordinates.size() / 6 },
			{ 504, freeDirtChunkCoordinates.size() / 6 },
			{ 603, freeDirtChunkCoordinates.size() / 6 },
			{ 604, freeDirtChunkCoordinates.size() / 6 }
		});

	std::pair<TextureId, uint64_t> dirtCamperEnemyQuota(2, freeDirtChunkCoordinates.size() / 6);

	std::queue<std::pair<ItemId, uint64_t>> gloomResourceQuota(
		{
			{ 505, freeGloomChunkCoordinates.size() / 6 },
			{ 506, freeGloomChunkCoordinates.size() / 6 },
			{ 605, freeGloomChunkCoordinates.size() / 6 },
			{ 606, freeGloomChunkCoordinates.size() / 6 }
		});

	std::pair<TextureId, uint64_t> gloomCamperEnemyQuota(3, freeGloomChunkCoordinates.size() / 6);

	const std::unordered_map<ItemId, ResourceNode> resourceNodeData(
		std::move(
			this->loadResourceNodeData_()));

	std::unordered_map<TextureId, CamperEnemyTemplate> camperEnemyTemplateData(
		std::move(
			this->loadCamperEnemyTemplateData_()));

	this->fillBiomeChunks_(
		freeGrassChunkCoordinates,
		grassResourceQuota,
		grassCamperEnemyQuota,
		engine,
		resourceNodeData,
		camperEnemyTemplateData);

	this->fillBiomeChunks_(
		freeDirtChunkCoordinates,
		dirtResourceQuota,
		dirtCamperEnemyQuota,
		engine,
		resourceNodeData,
		camperEnemyTemplateData);

	this->fillBiomeChunks_(
		freeGloomChunkCoordinates,
		gloomResourceQuota,
		gloomCamperEnemyQuota,
		engine,
		resourceNodeData,
		camperEnemyTemplateData);
}

void Map::spreadBiomeChunks_(
	const sf::Vector2u &chunkCoordinate,
	const sf::Vector2u &mapChunkSize,
	std::vector<std::vector<ChunkBiome>> &chunkBiomeMap,
	ChunkBiome chunkBiome) const
{
	const float chanceDecay = 0.25f;
	float expandChance = 1.0f;

	std::mt19937 &eng = Random::getInstance().getEngine();
	std::uniform_real_distribution<float> rollDis(0.0f, 1.0f);

	std::queue<Coordinate> queue;
	std::unordered_set<Coordinate> visited;

	queue.push(chunkCoordinate);
	visited.emplace(chunkCoordinate);

	while (!queue.empty())
	{
		const sf::Vector2u currentChunkCoordinate = queue.front().getPosition();
		queue.pop();

		chunkBiomeMap[currentChunkCoordinate.y][currentChunkCoordinate.x] = chunkBiome;

		std::vector<Coordinate> nextChunkCoordinates;

		if (currentChunkCoordinate.x > 0)
		{
			nextChunkCoordinates.emplace_back(
				sf::Vector2u(
					currentChunkCoordinate.x - 1,
					currentChunkCoordinate.y));
		}

		if (currentChunkCoordinate.x < mapChunkSize.x - 1)
		{
			nextChunkCoordinates.emplace_back(
				sf::Vector2u(
					currentChunkCoordinate.x + 1,
					currentChunkCoordinate.y));
		}

		if (currentChunkCoordinate.y > 0)
		{
			nextChunkCoordinates.emplace_back(
				sf::Vector2u(
					currentChunkCoordinate.x,
					currentChunkCoordinate.y - 1));
		}

		if (currentChunkCoordinate.y < mapChunkSize.y - 1)
		{
			nextChunkCoordinates.emplace_back(
				sf::Vector2u(
					currentChunkCoordinate.x,
					currentChunkCoordinate.y + 1));
		}

		for (const Coordinate &nextChunkCoordinate : nextChunkCoordinates)
		{
			if (visited.find(nextChunkCoordinate) != visited.end()
				|| rollDis(eng) > expandChance)
			{
				continue;
			}

			queue.push(nextChunkCoordinate);
			visited.emplace(nextChunkCoordinate);
		}

		expandChance *= chanceDecay;
	}
}

void Map::fillChunk_(
	const sf::Vector2u &chunkCoordinate,
	std::uniform_int_distribution<TextureId> &tileTextureIdDis,
	std::mt19937 &engine,
	const TextureData &textureData)
{
	const sf::Vector2u chunkMapCoordinate(chunkCoordinate * Constants::Chunk::size);

	for (uint32_t offsetRow = 0; offsetRow < Constants::Chunk::size; ++offsetRow)
	{
		for (uint32_t offsetCol = 0; offsetCol < Constants::Chunk::size; ++offsetCol)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offsetCol,
						chunkMapCoordinate.y + offsetRow),
					textureData.getTexture(
						tileTextureIdDis(
							engine))));
		}
	}
}

void Map::fillChunkWithBorders(
	const sf::Vector2u &chunkCoordinate,
	ChunkBiome chunkBiome,
	const std::vector<std::vector<ChunkBiome>> &chunkBiomeMap,
	const sf::Vector2u &mapChunkSize,
	std::uniform_int_distribution<TextureId> &fillTileTextureIdDis,
	std::mt19937 &engine,
	const TextureData &textureData,
	TextureId borderTopTextureId,
	TextureId borderBottomTextureId,
	TextureId borderLeftTextureId,
	TextureId borderRightTextureId,
	TextureId borderTopLeftTextureId,
	TextureId borderTopRightTextureId,
	TextureId borderBottomLeftTextureId,
	TextureId borderBottomRightTextureId,
	TextureId borderCornerTopLeftTextureId,
	TextureId borderCornerTopRightTextureId,
	TextureId borderCornerBottomLeftTextureId,
	TextureId borderCornerBottomRightTextureId)
{
	const sf::Vector2u chunkMapCoordinate(chunkCoordinate * Constants::Chunk::size);

	const bool borderTop = chunkCoordinate.y > 0 && chunkBiomeMap[chunkCoordinate.y - 1][chunkCoordinate.x] != chunkBiome;
	const bool borderBottom = chunkCoordinate.y < mapChunkSize.y - 1 && chunkBiomeMap[chunkCoordinate.y + 1][chunkCoordinate.x] != chunkBiome;
	const bool borderLeft = chunkCoordinate.x > 0 && chunkBiomeMap[chunkCoordinate.y][chunkCoordinate.x - 1] != chunkBiome;
	const bool borderRight = chunkCoordinate.x < mapChunkSize.x - 1 && chunkBiomeMap[chunkCoordinate.y][chunkCoordinate.x + 1] != chunkBiome;

	for (uint32_t offsetRow = 1; offsetRow < Constants::Chunk::size - 1; ++offsetRow)
	{
		for (uint32_t offsetCol = 1; offsetCol < Constants::Chunk::size - 1; ++offsetCol)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offsetCol,
						chunkMapCoordinate.y + offsetRow),
					textureData.getTexture(
						fillTileTextureIdDis(
							engine))));
		}
	}

	if (borderTop)
	{
		tileVisibility_.add(
			new Tile(
				sf::Vector2u(
					chunkMapCoordinate.x,
					chunkMapCoordinate.y),
				textureData.getTexture(
					(borderLeft
						? borderTopLeftTextureId
						: borderTopTextureId))));

		tileVisibility_.add(
			new Tile(
				sf::Vector2u(
					chunkMapCoordinate.x + Constants::Chunk::size - 1,
					chunkMapCoordinate.y),
				textureData.getTexture(
					(borderRight
						? borderTopRightTextureId
						: borderTopTextureId))));

		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offset,
						chunkMapCoordinate.y),
					textureData.getTexture(
						borderTopTextureId)));
		}
	}
	else
	{
		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offset,
						chunkMapCoordinate.y),
					textureData.getTexture(
						fillTileTextureIdDis(
							engine))));
		}

		if (!borderLeft)
		{
			bool existsDiagonal = (chunkCoordinate.x > 0
				&& chunkCoordinate.y > 0
				&& chunkBiomeMap[chunkCoordinate.y - 1][chunkCoordinate.x - 1] == chunkBiome);

			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y),
					textureData.getTexture(
						(existsDiagonal
							? fillTileTextureIdDis(engine)
							: borderCornerTopLeftTextureId))));
		}

		if (!borderRight)
		{
			bool existsDiagonal = (chunkCoordinate.x < mapChunkSize.x - 1
				&& chunkCoordinate.y > 0
				&& chunkBiomeMap[chunkCoordinate.y - 1][chunkCoordinate.x + 1] == chunkBiome);

			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y),
					textureData.getTexture(
						(existsDiagonal
							? fillTileTextureIdDis(engine)
							: borderCornerTopRightTextureId))));
		}
	}

	if (borderBottom)
	{
		tileVisibility_.add(
			new Tile(
				sf::Vector2u(
					chunkMapCoordinate.x,
					chunkMapCoordinate.y + Constants::Chunk::size - 1),
				textureData.getTexture(
					(borderLeft
						? borderBottomLeftTextureId
						: borderBottomTextureId))));

		tileVisibility_.add(
			new Tile(
				sf::Vector2u(
					chunkMapCoordinate.x + Constants::Chunk::size - 1,
					chunkMapCoordinate.y + Constants::Chunk::size - 1),
				textureData.getTexture(
					(borderRight
						? borderBottomRightTextureId
						: borderBottomTextureId))));

		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offset,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						borderBottomTextureId)));
		}
	}
	else
	{
		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + offset,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						fillTileTextureIdDis(
							engine))));
		}

		if (!borderLeft)
		{
			bool existsDiagonal = (chunkCoordinate.x > 0
				&& chunkCoordinate.y < mapChunkSize.y - 1
				&& chunkBiomeMap[chunkCoordinate.y + 1][chunkCoordinate.x - 1] == chunkBiome);

			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						(existsDiagonal
							? fillTileTextureIdDis(engine)
							: borderCornerBottomLeftTextureId))));
		}

		if (!borderRight)
		{
			bool existsDiagonal = (chunkCoordinate.x < mapChunkSize.x - 1
				&& chunkCoordinate.y < mapChunkSize.y - 1
				&& chunkBiomeMap[chunkCoordinate.y + 1][chunkCoordinate.x + 1] == chunkBiome);
			
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						(existsDiagonal
							? fillTileTextureIdDis(engine)
							: borderCornerBottomRightTextureId))));
		}
	}

	if (borderLeft)
	{
		if (!borderTop)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y),
					textureData.getTexture(
						borderLeftTextureId)));
		}
		if (!borderBottom)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						borderLeftTextureId)));
		}

		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y + offset),
					textureData.getTexture(
						borderLeftTextureId)));
		}
	}
	else
	{
		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x,
						chunkMapCoordinate.y + offset),
					textureData.getTexture(
						fillTileTextureIdDis(
							engine))));
		}
	}

	if (borderRight)
	{
		if (!borderTop)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y),
					textureData.getTexture(
						borderRightTextureId)));
		}
		if (!borderBottom)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y + Constants::Chunk::size - 1),
					textureData.getTexture(
						borderRightTextureId)));
		}

		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y + offset),
					textureData.getTexture(
						borderRightTextureId)));
		}
	}
	else
	{
		for (uint32_t offset = 1; offset < Constants::Chunk::size - 1; ++offset)
		{
			tileVisibility_.add(
				new Tile(
					sf::Vector2u(
						chunkMapCoordinate.x + Constants::Chunk::size - 1,
						chunkMapCoordinate.y + offset),
					textureData.getTexture(
						fillTileTextureIdDis(
							engine))));
		}
	}
}

void Map::fillBiomeChunks_(
	std::unordered_set<Coordinate> &freeChunkCoordinates,
	std::queue<std::pair<ItemId, uint64_t>> &resourceQuota,
	std::pair<TextureId, uint64_t> &camperEnemyQuota,
	std::mt19937 &engine,
	const std::unordered_map<ItemId, ResourceNode> &resourceNodeData,
	const std::unordered_map<TextureId, CamperEnemyTemplate> &camperEnemyTemplateData)
{
	while (!freeChunkCoordinates.empty())
	{
		std::uniform_int_distribution<size_t> freeGrassChunkCoordinatesDis(0, freeChunkCoordinates.size() - 1);

		const size_t index = freeGrassChunkCoordinatesDis(engine);

		auto it = freeChunkCoordinates.begin();

		for (size_t i = 0; i < index; ++i)
		{
			++it;
		}

		const sf::Vector2u chunkCoordinate = it->getPosition();
		freeChunkCoordinates.erase(it);

		if (!resourceQuota.empty())
		{
			std::pair<ItemId, uint64_t> &quota = resourceQuota.front();

			this->generateResourceNodeChunk_(
				chunkCoordinate,
				resourceNodeData.at(
					quota.first));

			if (--quota.second == 0)
			{
				resourceQuota.pop();
			}
		}
		else if (camperEnemyQuota.second > 0)
		{
			this->generateCamperEnemyChunk_(
				chunkCoordinate,
				camperEnemyTemplateData.at(
					camperEnemyQuota.first));

			--camperEnemyQuota.second;
		}
		else
		{
			break;
		}
	}
}

void Map::generateResourceNodeChunk_(
	const sf::Vector2u &chunkCoordinate,
	const ResourceNode &resourceNode)
{
	const sf::Vector2u chunkMapCoordinate(chunkCoordinate * Constants::Chunk::size);
	const uint32_t halfChunkSize = static_cast<uint32_t>(Constants::Chunk::size * 0.5f);

	std::mt19937 &eng = Random::getInstance().getEngine();
	std::uniform_real_distribution<float> rollDis(0.0f, 1.0f);

	const float chanceDecay = 0.5f;
	float expandChance = 1.0f;

	std::queue<Coordinate> queue;
	std::unordered_set<Coordinate> visited;

	const Coordinate centerCoordinate(
		sf::Vector2u(
			chunkMapCoordinate.x + halfChunkSize,
			chunkMapCoordinate.y + halfChunkSize));

	queue.push(centerCoordinate);
	visited.emplace(centerCoordinate);

	while (!queue.empty())
	{
		const sf::Vector2u currentCoordinate = queue.front().getPosition();
		queue.pop();

		resourceNodeVisibility_.add(
			resourceNode.clone(
				currentCoordinate));

		std::vector<Coordinate> nextCoordinates;

		if (currentCoordinate.x > chunkMapCoordinate.x)
		{
			nextCoordinates.emplace_back(
				sf::Vector2u(
					currentCoordinate.x - 1,
					currentCoordinate.y));
		}

		if (currentCoordinate.x < chunkMapCoordinate.x + Constants::Chunk::size - 1)
		{
			nextCoordinates.emplace_back(
				sf::Vector2u(
					currentCoordinate.x + 1,
					currentCoordinate.y));
		}

		if (currentCoordinate.y > chunkMapCoordinate.y)
		{
			nextCoordinates.emplace_back(
				sf::Vector2u(
					currentCoordinate.x,
					currentCoordinate.y - 1));
		}

		if (currentCoordinate.y < chunkMapCoordinate.y + Constants::Chunk::size - 1)
		{
			nextCoordinates.emplace_back(
				sf::Vector2u(
					currentCoordinate.x,
					currentCoordinate.y + 1));
		}

		for (const Coordinate &nextCoordinate : nextCoordinates)
		{
			if (visited.find(nextCoordinate) != visited.end()
				|| rollDis(eng) > expandChance)
			{
				continue;
			}

			queue.push(nextCoordinate);
			visited.emplace(nextCoordinate);
		}

		expandChance *= chanceDecay;
	}
}

void Map::generateCamperEnemyChunk_(
	const sf::Vector2u &chunkCoordinate,
	const CamperEnemyTemplate &camperEnemyTemplate)
{
	const TextureData &textureData = TextureData::getInstance();

	const sf::Vector2u chunkMapCoordinate(chunkCoordinate * Constants::Chunk::size);

	const uint32_t minOffset = static_cast<uint32_t>(Constants::Chunk::size * 0.25f);
	const uint32_t maxOffset = static_cast<uint32_t>(Constants::Chunk::size * 0.75f);

	const sf::Vector2u minSpawnCoordinate(
		chunkMapCoordinate.x + minOffset,
		chunkMapCoordinate.y + minOffset);

	const sf::Vector2u maxSpawnCoordinate(
		chunkMapCoordinate.x + maxOffset,
		chunkMapCoordinate.y + maxOffset);

	const std::vector<sf::Vector2u> camperEnemySpawnCoordinates(
		{
			sf::Vector2u(
				minSpawnCoordinate.x + 1,
				minSpawnCoordinate.y),

			sf::Vector2u(
				maxSpawnCoordinate.x,
				minSpawnCoordinate.y + 1),

			sf::Vector2u(
				minSpawnCoordinate.x,
				maxSpawnCoordinate.y - 1),

			sf::Vector2u(
				maxSpawnCoordinate.x - 1,
				maxSpawnCoordinate.y)
		});

	for (const sf::Vector2u &camperEnemySpawnCoordinate : camperEnemySpawnCoordinates)
	{
		camperEnemyVisibility_.add(
			camperEnemyTemplate.create(
				camperEnemySpawnCoordinate,
				camperEnemyVisibility_.getPartition()));
	}
}

std::unordered_map<ItemId, ResourceNode> Map::loadResourceNodeData_() const
{
	const std::string filePath = "./data/resource-nodes.txt";

	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in Map::loadResourceNodeData_\n", filePath.c_str());
		return {};
	}

	std::unordered_map<ItemId, ResourceNode> resourceNodeData;

	std::string line;
	std::stringstream ss;

	ItemId itemId;
	TextureId textureId;
	TextureId emptyTextureId;
	uint64_t numItems;
	uint64_t requiredPower;
	float harvestTime;
	std::string resourceTypeString;
	
	while (std::getline(in, line))
	{
		ss.clear();
		ss.str(line);

		ss	>> itemId
			>> textureId
			>> emptyTextureId
			>> numItems
			>> requiredPower
			>> harvestTime
			>> resourceTypeString;

		ResourceType resourceType = ResourceType::None;

		if (resourceTypeString == "WOOD")
		{
			resourceType = ResourceType::Wood;
		}
		else if (resourceTypeString == "STONE")
		{
			resourceType = ResourceType::Stone;
		}

		resourceNodeData.emplace(
			itemId,
			ResourceNode(
				sf::Vector2u(0, 0),
				textureId,
				emptyTextureId,
				resourceType,
				itemId,
				numItems,
				static_cast<uint8_t>(requiredPower),
				harvestTime));
	}

	return resourceNodeData;
}

std::unordered_map<TextureId, CamperEnemyTemplate> Map::loadCamperEnemyTemplateData_() const
{
	const std::string filePath = "./data/enemies.txt";

	std::ifstream in(filePath);

	if (!in.is_open())
	{
		fprintf(stderr, "Failed to open \"%s\" in Map::loadCamperEnemyTemplateData_\n", filePath.c_str());
		return {};
	}

	const TextureData &textureData = TextureData::getInstance();

	std::unordered_map<TextureId, CamperEnemyTemplate> camperEnemyTemplateData;

	std::string line;
	std::stringstream ss;

	TextureId animationTextureId;
	uint64_t health;
	uint64_t damage;
	float speed;
	float attackRadius;
	float attackSecs;
	uint64_t numHelmetTextureIds;
	uint64_t numChestplateTextureIds;
	TextureId helmetTextureId;
	TextureId chestplateTextureId;

	while (std::getline(in, line))
	{
		std::vector<TextureId> helmetTextureIds;
		std::vector<TextureId> chestplateTextureIds;

		ss.clear();
		ss.str(line);

		ss >> animationTextureId >> health >> damage >> speed >> attackRadius >> attackSecs;

		ss >> numHelmetTextureIds;

		for (uint64_t i = 0; i < numHelmetTextureIds; ++i)
		{
			ss >> helmetTextureId;
			helmetTextureIds.emplace_back(helmetTextureId);
		}

		ss >> numChestplateTextureIds;

		for (uint64_t i = 0; i < numChestplateTextureIds; ++i)
		{
			ss >> chestplateTextureId;
			chestplateTextureIds.emplace_back(chestplateTextureId);
		}

		camperEnemyTemplateData.emplace(
			animationTextureId,
			CamperEnemyTemplate(
				animationTextureId,
				helmetTextureIds,
				chestplateTextureIds,
				health,
				damage,
				speed,
				attackRadius,
				attackSecs));
	}

	return camperEnemyTemplateData;
}