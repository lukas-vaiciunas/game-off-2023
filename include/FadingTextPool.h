#pragma once

#include "Pool.h"
#include "Listener.h"
#include "FadingText.h"

class FadingTextPool :
	public Pool<FadingText>,
	public Listener,
	public WorldDrawable
{
public:
	FadingTextPool(Size capacity);

	void onEvent(const Event &ev) override;

	void update(float deltaTime);

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
};