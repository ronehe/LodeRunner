#include "..\include\Button.h"

Button::Button(const float& xPos, const float& yPos, const sf::Vector2f& size, const sf::Texture& texture)
	: m_sprite(texture)
{
	m_sprite.setPosition(sf::Vector2f(xPos, yPos));
	m_sprite.setScale(size.x, size.y);
}

sf::Sprite Button::getSprite() const
{
	return m_sprite;
}

void Button::setColor(const sf::Color& color)
{
	m_sprite.setColor(color);
}
