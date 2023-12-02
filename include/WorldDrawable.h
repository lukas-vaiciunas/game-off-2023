#pragma once

namespace sf
{
	class RenderTarget;
	class RenderStates;
	template<typename> class Vector2;
	typedef Vector2<float> Vector2f;
}

class WorldDrawable
{
public:
	WorldDrawable() = default;

	virtual ~WorldDrawable() = default;

	virtual void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const = 0;
};