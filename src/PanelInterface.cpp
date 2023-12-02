#include "PanelInterface.h"
#include "TextureData.h"
#include "Config.h"

PanelInterface::PanelInterface(
	const sf::Vector2f &centerPosition,
	const sf::String &titleString,
	TextureId panelTextureId)
	:
	Interface(
		sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(0.0f, 0.0f)),
	titleText_(),
	panelSprite_(TextureData::getInstance().getTexture(panelTextureId))
{
	size_ = panelSprite_.getSize();
	position_ = centerPosition - size_ * 0.5f;

	panelSprite_.setPosition(position_);

	titleText_.setString(titleString);
	titleText_.setCharacterSize(Config::Text::Size::large);
	titleText_.setFillColor(sf::Color(225, 225, 225));
	titleText_.setOutlineColor(sf::Color(0, 0, 0));

	const sf::FloatRect titleTextLocalBounds = titleText_.getLocalBounds();

	titleText_.setOrigin(
		titleTextLocalBounds.left + titleTextLocalBounds.width * 0.5f,
		titleTextLocalBounds.top + titleTextLocalBounds.height * 0.55f);

	titleText_.setInterfacePosition(
		sf::Vector2f(
			position_.x + size_.x * 0.5f,
			position_.y));
}