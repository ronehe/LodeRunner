#include <Enemy.h>
#include <iostream>

int Enemy::m_total_num_of_enemies = 0;

Enemy::Enemy(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const float& speed, const Direction& direction) :
	MovingObject(tex, pos, size, speed, direction) {

	m_total_num_of_enemies++;
}
void Enemy::kill(Player& player) {
	player.die();
}

int Enemy::getTotalNumEnemies() {

	return m_total_num_of_enemies;
}

int Enemy::getDefaultVelocity() {

	return ENEMY_DEFAULT_VELOCITY;
}

void Enemy::move(const float& deltaTime) {

	sf::Texture* tex;
	(m_direction == Direction::RIGHT || m_direction == Direction::LEFT) ?
		(tex = Resources::getInstance().getEnemyTexture(1)) :
		(tex = Resources::getInstance().getEnemyTexture(0));
	setAnimation(m_direction, *tex);
	MovingObject::move(deltaTime);
}

void Enemy::handleCollision(GameObject* gameObj) {

	gameObj->handleCollision(this);
}

void Enemy::changeDirection() {

	if (m_direction == Direction::LEFT) m_direction = Direction::RIGHT;
	else m_direction = Direction::LEFT;
}

Enemy::~Enemy() {

	m_total_num_of_enemies--;
}