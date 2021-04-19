#pragma once

#include "MovingObject.h"
#include "Wall.h"
#include "Ladder.h"

class ConstEnemy;

class Enemy :public MovingObject {
public:
	Enemy(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const float& speed, const Direction& direction);
	virtual void setPlayerPos(const sf::Vector2f&) {}
	void kill(Player&);
	void move(const float& deltaTime);
	int getDefaultVelocity();
	static int getTotalNumEnemies();
	virtual ~Enemy();
	void handleCollision(GameObject*) override;
	virtual void changeDirection();
private:
	static int m_total_num_of_enemies;
};