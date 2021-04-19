#pragma once

#include <SFML/Graphics.hpp>


class Button {
public:
	Button(const float& xPos, const float& yPos,const sf::Vector2f&, const sf::Texture& texture);
	sf::Sprite getSprite() const;
	void setColor(const sf::Color&);

private:
	sf::Sprite m_sprite;
};