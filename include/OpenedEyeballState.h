#pragma once

#include "EyeballState.h"
#include "Shakable.h"
#include "Animation.h"
#include "InterfaceSprite.h"
#include "InterfaceText.h"

class OpenedEyeballState :
	public EyeballState,
	public Shakable
{
public:
	OpenedEyeballState(
		const sf::Vector2f &position,
		const std::string &textString);

	void update(float deltaTime) override;

	bool isHovered() const override;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &scale) const override;
private:
	Animation<InterfaceSprite> animation_;

	InterfaceText text_;
	std::string textString_;
	
	AlarmClock writeClock_;
	size_t writeIndex_;

	AlarmClock durationClock_;

	sf::Vector2f position_;

	void setTextString_(const std::string &string);
};