#include "MainMenuTitleText.h"
#include "Config.h"

MainMenuTitleText::MainMenuTitleText(const sf::Vector2f &centerWindowPosition) :
	InterfaceDrawable(),
	banishedText_(),
	preyText_()
{
	const float gap = 1.0f * Config::Interface::scale;

	banishedText_.setString("Banished");
	banishedText_.setCharacterSize(Config::Text::Size::huge);
	banishedText_.setFillColor(sf::Color(168, 160, 236));
	banishedText_.setOutlineColor(sf::Color(0, 0, 0));
	banishedText_.setPosition(
		sf::Vector2f(
			centerWindowPosition.x,
			centerWindowPosition.y - gap * 0.5f));

	const sf::FloatRect banishedTextLocalBounds = banishedText_.getLocalBounds();

	banishedText_.setOrigin(
		banishedTextLocalBounds.left + banishedTextLocalBounds.width * 0.5f,
		banishedTextLocalBounds.top + banishedTextLocalBounds.height);

	preyText_.setString("Prey");
	preyText_.setCharacterSize(Config::Text::Size::huge);
	preyText_.setFillColor(sf::Color(252, 224, 140));
	preyText_.setOutlineColor(sf::Color(0, 0, 0));
	preyText_.setPosition(
		sf::Vector2f(
			centerWindowPosition.x,
			centerWindowPosition.y + gap * 0.5f));

	const sf::FloatRect preyTextLocalBounds = preyText_.getLocalBounds();

	preyText_.setOrigin(
		preyTextLocalBounds.left + preyTextLocalBounds.width * 0.5f,
		preyTextLocalBounds.top);
}

void MainMenuTitleText::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	banishedText_.draw(target, states, scale);
	preyText_.draw(target, states, scale);
}