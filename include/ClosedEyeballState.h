#pragma once

#include "EyeballState.h"
#include "SpriteButton.h"

class ClosedEyeballState : public EyeballState
{
public:
	ClosedEyeballState(const sf::Vector2f &position);
	
	void update(float deltaTime) override;
	void updateOnMouseMove(const sf::Vector2f &mouseInterfacePosition) override;
	void updateOnMouseButtonPress(sf::Mouse::Button button) override;
	void updateOnMouseButtonRelease(sf::Mouse::Button button) override;

	bool isHovered() const override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	SpriteButton spriteButton_;
};