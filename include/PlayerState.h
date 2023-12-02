#pragma once

class Player;

class PlayerState
{
public:
	PlayerState(Player &player);

	virtual ~PlayerState() = default;

	virtual void update(float deltaTime) {};
protected:
	Player &player_;
};