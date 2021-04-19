#pragma once

#include "Enemy.h"

class ConstEnemy :public Enemy {
public:
	using Enemy::Enemy;
	void setDirection() override;
	void changeDirection() override;
private:
	bool m_goingRight = true;
};