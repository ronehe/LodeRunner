#include "ConstEnemy.h"
#include <iostream>


void ConstEnemy::setDirection()
{
	Resources& r = Resources::getInstance();
	auto defaultDirection = MovingObject::defaultDirection();
	if (defaultDirection == Direction::DOWN) {
		m_goingRight = !m_goingRight;
	}
	if (m_goingRight) {
		m_direction = Direction::RIGHT;
		this->setAnimation(Direction::RIGHT, *r.getEnemyTexture(1));
	}
	else {
		m_direction = Direction::LEFT;
		this->setAnimation(Direction::LEFT, *r.getEnemyTexture(1));
	}
}

void ConstEnemy::changeDirection() {
	m_goingRight = !m_goingRight;
}
