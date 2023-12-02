#pragma once

#include "Listener.h"
#include "InterfaceSprite.h"

class HealthInterface :
	public Listener,
	public InterfaceDrawable
{
public:
	HealthInterface(const sf::Vector2f &position);

	void onEvent(const Event &ev) override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	std::vector<InterfaceSprite> barSprites_;
	uint8_t numComponents_;

	InterfaceSprite iconSprite_;

	void update_(float fillRatio);
};