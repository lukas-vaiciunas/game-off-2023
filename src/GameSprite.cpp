#include "GameSprite.h"
#include <SFML/Graphics/Texture.hpp>

GameSprite::GameSprite() :
	GameSprite(nullptr, sf::Vector2f(0.0f, 0.0f))
{}

GameSprite::GameSprite(const sf::Texture &texture) :
	GameSprite(&texture, sf::Vector2f(texture.getSize()))
{}

GameSprite::GameSprite(const sf::Texture &texture, const sf::Vector2f &size) :
	GameSprite(&texture, size)
{}

GameSprite::GameSprite(const sf::Texture *texture, const sf::Vector2f &size) :
	sf::Transformable(),
	texture_(texture),
	vertices_(sf::PrimitiveType::Triangles),
	size_(size)
{
	if (size_.x != 0.0f && size_.y != 0.0f)
	{
		this->initialize_();
	}
}

void GameSprite::setTexture(const sf::Texture &texture)
{
	texture_ = &texture;

	const sf::Vector2f textureSize(texture.getSize());

	if (size_ == textureSize)
	{
		return;
	}

	size_ = textureSize;

	this->initialize_();
}

void GameSprite::setTexturePosition(const sf::Vector2f &texturePosition)
{
	this->updateTextureCoordinates_(texturePosition);
}

void GameSprite::setAlpha(uint8_t alpha)
{
	for (size_t i = 0; i < vertices_.getVertexCount(); ++i)
	{
		vertices_[i].color.a = alpha;
	}
}

const sf::Texture *GameSprite::getTexture() const
{
	return texture_;
}

const sf::Vector2f &GameSprite::getSize() const
{
	return size_;
}

void GameSprite::initialize_()
{
	vertices_.clear();
	vertices_.resize(6);

	const sf::Vector2f topLeftOffset(0.0f, 0.0f);
	const sf::Vector2f topRightOffset(size_.x, 0.0f);
	const sf::Vector2f bottomLeftOffset(0.0f, size_.y);
	const sf::Vector2f bottomRightOffset(size_);

	vertices_[0].position = topLeftOffset;
	vertices_[1].position = topRightOffset;
	vertices_[2].position = bottomLeftOffset;
	vertices_[3].position = bottomLeftOffset;
	vertices_[4].position = topRightOffset;
	vertices_[5].position = bottomRightOffset;

	this->updateTextureCoordinates_(sf::Vector2f(0.0f, 0.0f));
}

void GameSprite::updateTextureCoordinates_(const sf::Vector2f &texturePosition)
{
	const sf::Vector2f topLeftOffset(0.0f, 0.0f);
	const sf::Vector2f topRightOffset(size_.x, 0.0f);
	const sf::Vector2f bottomLeftOffset(0.0f, size_.y);
	const sf::Vector2f bottomRightOffset(size_);

	vertices_[0].texCoords = texturePosition + topLeftOffset;
	vertices_[1].texCoords = texturePosition + topRightOffset;
	vertices_[2].texCoords = texturePosition + bottomLeftOffset;
	vertices_[3].texCoords = texturePosition + bottomLeftOffset;
	vertices_[4].texCoords = texturePosition + topRightOffset;
	vertices_[5].texCoords = texturePosition + bottomRightOffset;
}