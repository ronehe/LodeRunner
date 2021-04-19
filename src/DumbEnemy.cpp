#include "DumbEnemy.h"


void DumbEnemy::setDirection()
{
	auto defaultDirection = MovingObject::defaultDirection();
	if (defaultDirection != Direction::STAND) {
		m_direction = defaultDirection;
		return;
	}

	if (m_direction == Direction::DOWN) {
		m_direction = Direction::RIGHT;
		return;
	}

	m_counter++;

	if (m_counter == 500) {
		m_counter = 0;
		if (rand() % 2 == 1) {

			auto direction = rand() % 5;
			switch (direction) {
			case 0:
				m_direction = Direction::LEFT;
				return;
			case 1:
				m_direction = Direction::RIGHT;
				 return;
			case 2:
				m_direction = Direction::UP;
				return;
			case 3:
				m_direction = Direction::DOWN;
				return;
			}
		}
	}
}
