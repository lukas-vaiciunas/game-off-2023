#pragma once

#include "InterfaceSprite.h"
#include "Animation.h"

class MainMenuBackdrop : public InterfaceDrawable
{
public:
	MainMenuBackdrop();

	void update(float deltaTime);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	enum class State : uint8_t
	{
		Expanding,
		Contracting
	};

	State state_;

	InterfaceSprite backdropSprite_;
	Animation<InterfaceSprite> playerAnimation_;

	float scale_;
	float minScale_;
	float maxScale_;
	float velScale_;
};