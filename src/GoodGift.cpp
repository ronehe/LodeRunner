#pragma once
#include "GoodGift.h"

GoodGift::GoodGift(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const int& value)
	:Gift(tex, pos, size), m_value(value)
{}
