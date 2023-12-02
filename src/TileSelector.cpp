#include "TileSelector.h"
#include "Map.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "Constants.h"
#include "Config.h"

TileSelector::TileSelector(Map &map) :
	WorldDrawable(),
	state_(State::Expand),
	map_(map),
	sprite_(TextureData::getInstance().getTexture(101)),
	text_(),
	mouseWorldPosition_(0.0f, 0.0f),
	coordinates_(0, 0),
	minScale_(0.95f),
	maxScale_(1.05f),
	scale_(1.0f),
	velScale_(0.375f)
{
	text_.setCharacterSize(Config::Text::Size::small);
	text_.setFillColor(sf::Color(225, 225, 225));
	text_.setOutlineColor(sf::Color(0, 0, 0));

	sprite_.setOrigin(sprite_.getSize() * 0.5f);

	this->updateSpritePosition_();
}

void TileSelector::update(float deltaTime, const sf::Vector2f &worldOffset)
{
	this->updateCoordinates_(worldOffset);

	switch (state_)
	{
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= maxScale_)
			{
				scale_ = maxScale_;
				state_ = State::Contract;
			}
			break;
		case State::Contract:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
	}

	const sf::Vector2f scale(scale_, scale_);

	sprite_.setScale(scale);
	text_.setScale(scale);
}

void TileSelector::updateOnMouseMove(const sf::Vector2f &mouseWorldPosition)
{
	mouseWorldPosition_ = mouseWorldPosition;
}

void TileSelector::updateOnMouseButtonPress(sf::Mouse::Button button)
{
	if (button != sf::Mouse::Button::Left)
	{
		return;
	}

	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = map_.getVisibleCamperEnemies();

	for (auto it = visibleCamperEnemies.begin(); it != visibleCamperEnemies.end(); ++it) // TODO speed this up
	{
		if (coordinates_ != it->second->getCoordinate())
		{
			continue;
		}

		EventQueue::getInstance().send(
			new EventMovePlayerAndAttack(
				it->second,
				map_));

		return;
	}

	const HunterEnemyPool &hunterEnemyPool = map_.getHunterEnemyPool();

	for (auto it = hunterEnemyPool.begin(); it != hunterEnemyPool.end(); ++it)
	{
		if (coordinates_ != (*it)->getCoordinate())
		{
			continue;
		}

		EventQueue::getInstance().send(
			new EventMovePlayerAndAttack(
				*it,
				map_));

		return;
	}

	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = map_.getVisibleResourceNodes();

	if (visibleResourceNodes.find(Coordinate(coordinates_)) != visibleResourceNodes.end())
	{
		EventQueue::getInstance().send(
			new EventMovePlayerAndHarvest(
				coordinates_,
				map_));
	}
	else
	{
		EventQueue::getInstance().send(
			new EventMovePlayer(
				coordinates_,
				map_));
	}
}

void TileSelector::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	sprite_.draw(target, states, offset, scale);
	text_.draw(target, states, offset, scale);
}

void TileSelector::updateCoordinates_(const sf::Vector2f &worldOffset)
{
	const sf::Vector2f mouseRelativePosition(mouseWorldPosition_ + worldOffset);

	if (mouseRelativePosition.x < 0.0f
		|| mouseRelativePosition.y < 0.0f)
	{
		return;
	}

	const float invTileSize = 1.0f / Constants::tileSize;

	sf::Vector2u coordinate = sf::Vector2u(mouseRelativePosition * invTileSize);

	if (this->updateEnemySelection_(coordinate, mouseRelativePosition))
	{
		return;
	}

	this->updateTileSelection_(coordinate);
}

bool TileSelector::updateEnemySelection_(
	const sf::Vector2u &coordinate,
	const sf::Vector2f &mouseRelativePosition)
{
	const float threshold = Constants::tileSize * 0.5f + 1.0f;

	const std::unordered_multimap<Coordinate, CamperEnemy *> &visibleCamperEnemies = map_.getVisibleCamperEnemies();

	for (auto it = visibleCamperEnemies.begin(); it != visibleCamperEnemies.end(); ++it)
	{
		const sf::Vector2f &camperEnemyCenterPosition = it->second->getCenterPosition();

		const sf::Vector2f topLeft(
			camperEnemyCenterPosition.x - threshold,
			camperEnemyCenterPosition.y - threshold);

		const sf::Vector2f bottomRight(
			camperEnemyCenterPosition.x + threshold,
			camperEnemyCenterPosition.y + threshold);

		if (mouseRelativePosition.x > topLeft.x
			&& mouseRelativePosition.x < bottomRight.x
			&& mouseRelativePosition.y > topLeft.y
			&& mouseRelativePosition.y < bottomRight.y)
		{
			coordinates_ = it->second->getCoordinate();
			sprite_.setPosition(camperEnemyCenterPosition);
			text_.setWorldPosition(camperEnemyCenterPosition);
			this->setTextString_("Attack");

			return true;
		}
	}

	const HunterEnemyPool &hunterEnemyPool = map_.getHunterEnemyPool(); // TODO change from HunterEnemyPool to unordered multimap and remove iterators from pool

	for (auto it = hunterEnemyPool.begin(); it != hunterEnemyPool.end(); ++it)
	{
		const sf::Vector2f &hunterEnemyCenterPosition = (*it)->getCenterPosition();

		const sf::Vector2f topLeft(
			hunterEnemyCenterPosition.x - threshold,
			hunterEnemyCenterPosition.y - threshold);

		const sf::Vector2f bottomRight(
			hunterEnemyCenterPosition.x + threshold,
			hunterEnemyCenterPosition.y + threshold);

		if (mouseRelativePosition.x > topLeft.x
			&& mouseRelativePosition.x < bottomRight.x
			&& mouseRelativePosition.y > topLeft.y
			&& mouseRelativePosition.y < bottomRight.y)
		{
			coordinates_ = (*it)->getCoordinate();
			sprite_.setPosition(hunterEnemyCenterPosition);
			text_.setWorldPosition(hunterEnemyCenterPosition);
			this->setTextString_("Attack");

			return true;
		}
	}

	return false;
}

void TileSelector::updateTileSelection_(const sf::Vector2u &coordinate)
{
	if (coordinates_ == coordinate)
	{
		return;
	}

	coordinates_ = coordinate;

	const std::unordered_map<Coordinate, ResourceNode *> &visibleResourceNodes = map_.getVisibleResourceNodes();

	auto it = visibleResourceNodes.find(coordinates_);

	if (it != visibleResourceNodes.end())
	{
		switch (it->second->getResourceType())
		{
			case ResourceType::Wood:
				this->setTextString_("Chop");
				break;
			case ResourceType::Stone:
				this->setTextString_("Mine");
				break;
		}
	}
	else
	{
		this->setTextString_("Move");
	}

	this->updateSpritePosition_();
}

void TileSelector::updateSpritePosition_()
{
	const sf::Vector2f centerPosition(
		sf::Vector2f(
			coordinates_.x + 0.5f,
			coordinates_.y + 0.5f) * static_cast<float>(Constants::tileSize));
	
	sprite_.setPosition(centerPosition);
	text_.setWorldPosition(centerPosition);
}

void TileSelector::setTextString_(const std::string &string)
{
	if (text_.getString() == string)
	{
		return;
	}

	text_.setString(string);

	const sf::FloatRect textLocalBounds = text_.getLocalBounds();

	text_.setOrigin(
		textLocalBounds.left + textLocalBounds.width * 0.5f,
		textLocalBounds.top + textLocalBounds.height + sprite_.getSize().y * 0.5f * Config::World::scale);
}