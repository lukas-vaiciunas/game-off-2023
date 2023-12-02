#include "HealthInterface.h"
#include "Event.h"
#include "TextureData.h"

HealthInterface::HealthInterface(const sf::Vector2f &position) :
	Listener({ EventType::UpdateHealthInterface }),
	InterfaceDrawable(),
	barSprites_(),
	numComponents_(12),
	iconSprite_(TextureData::getInstance().getTexture(2121))
{
	const sf::Vector2f &iconSpriteSize = iconSprite_.getSize();

	iconSprite_.setOrigin(
		sf::Vector2f(
			0.0f,
			iconSpriteSize.y * 0.5f));

	iconSprite_.setPosition(position);

	const sf::Texture &texture = TextureData::getInstance().getTexture(2201);
	const float barX = position.x + iconSpriteSize.x + 1.0f;

	for (uint8_t i = 0; i < numComponents_; ++i)
	{
		InterfaceSprite barSprite(texture);

		const sf::Vector2f &barSpriteSize = barSprite.getSize();

		barSprite.setOrigin(
			0.0f,
			barSpriteSize.y * 0.5f);

		barSprite.setPosition(
			sf::Vector2f(
				barX + (barSpriteSize.x - 1.0f) * i,
				position.y));

		barSprites_.emplace_back(
			std::move(
				barSprite));
	}
}

void HealthInterface::onEvent(const Event &ev)
{
	this->update_(
		static_cast<const EventUpdateHealthInterface &>(ev).getFillRatio());
}

void HealthInterface::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &scale) const
{
	iconSprite_.draw(target, states, scale);

	for (const InterfaceSprite &barSprite : barSprites_)
	{
		barSprite.draw(target, states, scale);
	}
}

void HealthInterface::update_(float fillRatio)
{
	const TextureData &textureData = TextureData::getInstance();
	const sf::Texture &emptyTexture = textureData.getTexture(2201);
	const sf::Texture &fullTexture = textureData.getTexture(2202);

	uint8_t numFull = static_cast<uint8_t>(numComponents_ * fillRatio);

	for (uint8_t i = 0; i < numFull; ++i)
	{
		barSprites_[i].setTexture(fullTexture);
	}

	for (uint8_t i = numFull; i < numComponents_; ++i)
	{
		barSprites_[i].setTexture(emptyTexture);
	}
}