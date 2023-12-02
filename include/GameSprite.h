#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class GameSprite : public sf::Transformable
{
public:
	GameSprite();
	GameSprite(const sf::Texture &texture);
	GameSprite(const sf::Texture &texture, const sf::Vector2f &size);

	virtual ~GameSprite() = default;

	void setTexture(const sf::Texture &texture);
	void setTexturePosition(const sf::Vector2f &texturePosition);
	void setAlpha(uint8_t alpha);

	const sf::Texture *getTexture() const;
	const sf::Vector2f &getSize() const;
protected:
	const sf::Texture *texture_;

	sf::VertexArray vertices_;
	sf::Vector2f size_;

	GameSprite(const sf::Texture *texture, const sf::Vector2f &size);

	void initialize_();
	void updateTextureCoordinates_(const sf::Vector2f &texturePosition);
};