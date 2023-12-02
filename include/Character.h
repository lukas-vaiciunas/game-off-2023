#pragma once

#include "Animation.h"
#include "WorldSprite.h"
#include "TextureId.h"

class Character : public WorldDrawable
{
public:
	Character(
		const sf::Vector2u &coordinate,
		float speed,
		const sf::Texture &texture);

	virtual ~Character() = default;

	virtual void update(float deltaTime);

	const sf::Vector2u &getCoordinate() const;
	const sf::Vector2f &getCenterPosition() const;
	const sf::Vector2f &getSize() const;

	void draw(
		sf::RenderTarget &target,
		const sf::RenderStates &states,
		const sf::Vector2f &offset,
		const sf::Vector2f &scale) const override;
protected:
	Animation<WorldSprite> animation_;

	sf::Vector2u coordinate_;

	float speed_;

	WorldSprite helmetSprite_;
	bool isHelmetEquipped_;

	WorldSprite chestplateSprite_;
	bool isChestplateEquipped_;

	void updateSpritePosition_();
	void updateHelmetPosition_();
	void updateChestplatePosition_();

	void setHelmetTexture_(TextureId textureId);
	void setChestplateTexture_(TextureId textureId);
};