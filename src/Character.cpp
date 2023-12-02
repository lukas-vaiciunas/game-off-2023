#include "Character.h"
#include "TextureData.h"
#include "Constants.h"

Character::Character(
	const sf::Vector2u &coordinate,
	float speed,
	const sf::Texture &texture)
	:
	WorldDrawable(),
	animation_(texture, sf::Vector2f(7.0f, 7.0f), 4, 0.25f),
	coordinate_(coordinate),
	speed_(speed),
	helmetSprite_(),
	isHelmetEquipped_(false),
	chestplateSprite_(),
	isChestplateEquipped_(false)
{
	animation_.setOrigin(animation_.getSize() * 0.5f);

	this->updateSpritePosition_();
}

void Character::update(float deltaTime)
{
	animation_.update(deltaTime);

	if (animation_.wasUpdated())
	{
		this->updateHelmetPosition_();
		this->updateChestplatePosition_();
	}
}

const sf::Vector2u &Character::getCoordinate() const
{
	return coordinate_;
}

const sf::Vector2f &Character::getCenterPosition() const
{
	return animation_.getPosition();
}

const sf::Vector2f &Character::getSize() const
{
	return animation_.getSize();
}

void Character::draw(
	sf::RenderTarget &target,
	const sf::RenderStates &states,
	const sf::Vector2f &offset,
	const sf::Vector2f &scale) const
{
	animation_.draw(target, states, offset, scale);

	if (isChestplateEquipped_)
	{
		chestplateSprite_.draw(target, states, offset, scale);
	}

	if (isHelmetEquipped_)
	{
		helmetSprite_.draw(target, states, offset, scale);
	}
}

void Character::updateSpritePosition_()
{
	animation_.setPosition(
		sf::Vector2f(
			coordinate_.x + 0.5f,
			coordinate_.y + 0.5f) * static_cast<float>(Constants::tileSize));

	this->updateHelmetPosition_();
	this->updateChestplatePosition_();
}

void Character::updateHelmetPosition_()
{
	const sf::Vector2f &centerPosition = this->getCenterPosition();

	float yOffset = (animation_.getCol() % 2 ? 1.0f : 0.0f);

	helmetSprite_.setPosition(
		sf::Vector2f(
			centerPosition.x,
			centerPosition.y - this->getSize().y * 0.5f + yOffset));
}

void Character::updateChestplatePosition_()
{
	const sf::Vector2f &centerPosition = this->getCenterPosition();
	const sf::Vector2f &size = this->getSize();

	float yOffset = (animation_.getCol() % 2 ? 1.0f : 0.0f);

	chestplateSprite_.setPosition(
		sf::Vector2f(
			centerPosition.x - size.x * 0.5f,
			centerPosition.y - size.y * 0.5f + 2.0f + yOffset));
}

void Character::setHelmetTexture_(TextureId textureId)
{
	if (textureId == 0)
	{
		isHelmetEquipped_ = false;
		return;
	}

	isHelmetEquipped_ = true;

	helmetSprite_.setTexture(
		TextureData::getInstance().getTexture(
			textureId));

	const sf::Vector2f &helmetSpriteSize = helmetSprite_.getSize();

	helmetSprite_.setOrigin(
		helmetSpriteSize.x * 0.5f,
		helmetSpriteSize.y - 1.0f);
}

void Character::setChestplateTexture_(TextureId textureId)
{
	if (textureId == 0)
	{
		isChestplateEquipped_ = false;
		return;
	}

	isChestplateEquipped_ = true;

	chestplateSprite_.setTexture(
		TextureData::getInstance().getTexture(
			textureId));
}