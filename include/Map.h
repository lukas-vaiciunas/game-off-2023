#pragma once

class CamperEnemyTemplate;
class TextureData;

#include "Listener.h"
#include "Tile.h"
#include "ResourceNode.h"
#include "CamperEnemy.h"
#include "ObjectVisibility.h"
#include "HunterEnemyPool.h"
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>

class Map : public Listener
{
public:
	Map();

	void onEvent(const Event &ev) override;

	void update(float deltaTime, const sf::Vector2u &playerCoordinate);

	void updateVisibility(const sf::Vector2u &playerCoordinate);

	std::vector<sf::Vector2u> getNavigableAdjacents(
		const sf::Vector2u &coordinate) const;

	const sf::Vector2u &getClosestCoordinate(
		const sf::Vector2u &from,
		const std::vector<sf::Vector2u> &options) const;

	const std::unordered_map<Coordinate, Tile *> &getVisibleTiles() const;
	const std::unordered_map<Coordinate, ResourceNode *> &getVisibleResourceNodes() const;
	const std::unordered_multimap<Coordinate, CamperEnemy *> &getVisibleCamperEnemies() const;
	const HunterEnemyPool &getHunterEnemyPool() const;
private:
	enum class ChunkBiome : uint8_t
	{
		Grass,
		Dirt,
		Gloom
	};

	ObjectVisibility<Tile, std::unordered_map<Coordinate, Tile *>> tileVisibility_;
	ObjectVisibility<ResourceNode, std::unordered_map<Coordinate, ResourceNode *>> resourceNodeVisibility_;
	ObjectVisibility<CamperEnemy, std::unordered_multimap<Coordinate, CamperEnemy *>> camperEnemyVisibility_;

	HunterEnemyPool hunterEnemyPool_;

	void initialize_();

	void spreadBiomeChunks_(
		const sf::Vector2u &chunkCoordinate,
		const sf::Vector2u &mapChunkSize,
		std::vector<std::vector<ChunkBiome>> &chunkBiomeMap,
		ChunkBiome chunkBiome) const;

	void fillChunk_(
		const sf::Vector2u &chunkCoordinate,
		std::uniform_int_distribution<TextureId> &tileTextureIdDis,
		std::mt19937 &engine,
		const TextureData &textureData);

	void fillChunkWithBorders(
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
		TextureId borderCornerBottomRightTextureId);

	void fillBiomeChunks_(
		std::unordered_set<Coordinate> &freeChunkCoordinates,
		std::queue<std::pair<ItemId, uint64_t>> &resourceQuota,
		std::pair<TextureId, uint64_t> &camperEnemyQuota,
		std::mt19937 &engine,
		const std::unordered_map<ItemId, ResourceNode> &resourceNodeData,
		const std::unordered_map<TextureId, CamperEnemyTemplate> &camperEnemyTemplateData);

	void generateResourceNodeChunk_(
		const sf::Vector2u &chunkCoordinate,
		const ResourceNode &resourceNode);

	void generateCamperEnemyChunk_(
		const sf::Vector2u &chunkCoordinate,
		const CamperEnemyTemplate &camperEnemyTemplate);

	std::unordered_map<ItemId, ResourceNode> loadResourceNodeData_() const;
	std::unordered_map<TextureId, CamperEnemyTemplate> loadCamperEnemyTemplateData_() const;
};