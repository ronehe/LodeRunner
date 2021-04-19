#pragma once

#include "Enemy.h"
#include <iostream>
class Ladder;

class SmartEnemy :public Enemy {
public:
	using Enemy::Enemy;
	SmartEnemy(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const float& , const Direction&, const Player& player);
	void setDirection() override;
	void setPlayerPos(const sf::Vector2f&);
	void updateAdjacentObjects(StaticObject* left,
		StaticObject* right,
		StaticObject* up,
		StaticObject* down,
		StaticObject* curr) override;

private:
	const Player& player;
	bool m_onLadder = false;
	sf::Vector2f m_playerCurPos;
};