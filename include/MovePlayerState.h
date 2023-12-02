#pragma once

#include "PlayerState.h"
#include <SFML/System/Vector2.hpp>
#include <stack>

class MovePlayerState : public PlayerState
{
public:
	MovePlayerState(
		Player &player,
		const std::stack<sf::Vector2u> &path);

	virtual ~MovePlayerState() = default;

	void update(float deltaTime) override;
protected:
	std::stack<sf::Vector2u> path_;

	void advance_();
	virtual void onArrival_();
};