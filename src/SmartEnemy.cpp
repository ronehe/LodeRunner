#include "SmartEnemy.h"


SmartEnemy::SmartEnemy(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& size, const float& speed, const Direction& direction, const Player& playerRef)
    : Enemy(texture, position, size, speed, direction), player(playerRef)
{
}

// The smartEnemy move relatively to the player position
void SmartEnemy::setDirection()
{
	auto defaultDirection = MovingObject::defaultDirection();
	if (defaultDirection != Direction::STAND) {
		m_direction = defaultDirection;
		return;
	}

	auto player_x = player.getPosition().x;
	auto player_y = player.getPosition().y;
	auto enemy_x = m_sprite.getPosition().x;
	auto enemy_y = m_sprite.getPosition().y;

	if (player_y == enemy_y) {
		m_onLadder = false;
		m_direction = Direction::LEFT;
		return;
	}

	if (player_y < enemy_y && m_onLadder) {
		m_direction = Direction::UP;
		return;
	}
	else if (player_y > enemy_y && m_onLadder) {

		if (player_x < enemy_x) {
			m_direction = Direction::LEFT;
			return;
		}
		else if (player_x > enemy_y) {
			m_direction = Direction::RIGHT;
			return;
		}
		else {
			m_direction = Direction::DOWN;
			return;
		}
	}
	else if (player_y < enemy_y && player_x < enemy_x) {
		m_onLadder = false;
		m_direction = Direction::LEFT;
		return;
	}
	else if (player_y < enemy_y && player_x > enemy_x) {
		m_onLadder = false;
		m_direction = Direction::RIGHT;
		return;
	}
	else if (player_y > enemy_y && player_x < enemy_x) {
		m_onLadder = false;
		m_direction = Direction::LEFT;
		return;
	}
	else if (player_y > enemy_y && player_x > enemy_x) {
		m_onLadder = false;
		m_direction = Direction::RIGHT;
		return;
	}
	else if (player_y == enemy_y && player_x > enemy_x) {
		m_onLadder = false;
		m_direction = Direction::RIGHT;
		return;
	}
	else if (player_y == enemy_y && player_x < enemy_x) {
		m_onLadder = false;
		m_direction = Direction::LEFT;
		return;
	}
}

void SmartEnemy::updateAdjacentObjects(StaticObject* left,
	StaticObject* right,
	StaticObject* up,
	StaticObject* down,
	StaticObject* curr) {
	MovingObject::updateAdjacentObjects(left, right, up, down, curr);

	if (dynamic_cast<Ladder*>(curr) || dynamic_cast<Ladder*>(up))
		m_onLadder = true;
	else
		m_onLadder = false;
}

void SmartEnemy::setPlayerPos(const sf::Vector2f& playerLoc)
{
    m_playerCurPos = playerLoc;
}
