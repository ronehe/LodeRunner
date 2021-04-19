#pragma once
#include "Gift.h"
#include "MovingObject.h"

class Board;
class BadGift : public Gift {
public:
	void handleCollision(Player* player);
	BadGift(const sf::Texture&, const sf::Vector2f& pos, const sf::Vector2f& size, Board* board);
private:
	bool m_addEnemy = false;
	Board* m_board;
};