#include "MovePlayerState.h"
#include "Player.h"
#include "Event.h"
#include "EventQueue.h"
#include "Constants.h"

MovePlayerState::MovePlayerState(
	Player &player,
	const std::stack<sf::Vector2u> &path)
	:
	PlayerState(player),
	path_(path)
{
	player_.animation_.setRow(1);

	if (player_.getCenterPosition() != sf::Vector2f(
		player_.coordinate_.x + 0.5f,
		player_.coordinate_.y + 0.5f) * static_cast<float>(Constants::tileSize))
	{
		path_.push(player_.coordinate_);
	}
}

void MovePlayerState::update(float deltaTime)
{
	const sf::Vector2f targetPosition(
		sf::Vector2f(
			player_.coordinate_.x + 0.5f,
			player_.coordinate_.y + 0.5f)
		* static_cast<float>(Constants::tileSize));

	const sf::Vector2f delta = targetPosition - player_.getCenterPosition();

	const float angle = atan2f(delta.y, delta.x);

	const sf::Vector2f velocity(
		sf::Vector2f(
			player_.speed_ * cosf(angle),
			player_.speed_ * sinf(angle))
		* deltaTime);

	const float distanceSq = delta.x * delta.x + delta.y * delta.y;
	const float velocitySq = velocity.x * velocity.x + velocity.y * velocity.y;

	if (distanceSq <= velocitySq)
	{
		player_.updateSpritePosition_();

		this->advance_();
	}
	else
	{
		player_.animation_.move(velocity);

		player_.updateHelmetPosition_();
		player_.updateChestplatePosition_();
	}

	player_.updateFootstepSounds_();
}

void MovePlayerState::advance_()
{
	if (path_.empty())
	{
		this->onArrival_();

		return;
	}

	player_.coordinate_ = path_.top();
	path_.pop();
}

void MovePlayerState::onArrival_()
{
	EventQueue::getInstance().send(
		new EventStopPlayer());
}