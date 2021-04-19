#pragma once

#include "Enemy.h"

class DumbEnemy :public Enemy {
public:
	using Enemy::Enemy;
	void setDirection() override;
private:
	int m_counter = 0;
};