#pragma once

class Map;

#include "WorldSprite.h"
#include "WorldText.h"
#include <SFML/Window/Mouse.hpp>

class TileSelector : public WorldDrawable
{
public:
	TileSelector(Map &map);

	void update(float deltaTime, const sf::Vector2f &worldOffset);
	void updateOnMouseMove(const sf::Vector2f &mouseWorldPosition);
	void updateOnMouseButtonPress(sf::Mouse::Button button);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
private:
	enum class State : uint8_t
	{
		Expand,
		Contract
	};

	State state_;

	Map &map_;

	WorldSprite sprite_;
	WorldText text_;

	sf::Vector2f mouseWorldPosition_;
	sf::Vector2u coordinates_;

	float minScale_;
	float maxScale_;
	float scale_;
	float velScale_;

	void updateCoordinates_(const sf::Vector2f &worldOffset);
	bool updateEnemySelection_(
		const sf::Vector2u &coordinate,
		const sf::Vector2f &mouseRelativePosition);
	void updateTileSelection_(const sf::Vector2u &coordinate);
	void updateSpritePosition_();

	void setTextString_(const std::string &string);
};