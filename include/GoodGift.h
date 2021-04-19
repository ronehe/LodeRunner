#pragma once

#include "Gift.h"
#include <MovingObject.h>
#include "Player.h"

class GoodGift : public Gift {
public:
	GoodGift(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const int&);
protected:
	int m_value;
};