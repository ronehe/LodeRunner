#include <Wall.h>

void Wall::handleCollision(Player* player)
{
	if(!m_wallTaken) player->stand();
}

void Wall::handleCollision(Enemy* enemy)
{
	if (!m_wallTaken) enemy->changeDirection();
}

void Wall::draw(sf::RenderWindow& window) {

	// If the wall has been removed by the player
	if (!(m_timer.getElapsedTime().asSeconds() < 3 && m_wallTaken)) {
		window.draw(m_sprite);
		m_timer.restart();
		m_wallTaken = false;
	}
 }

void Wall::remove() {

	m_wallTaken = true;
	m_timer.restart();
}

Direction Wall::direction_if_on_this_object(MovingObject& movingObj) {
	if (!m_wallTaken) {
		auto vec = sf::Vector2f(0, -getShapeGlobalBounds().height);
		movingObj.move(vec);
	}
	return Direction::STAND;
}

Direction Wall::direction_if_above_this_object(MovingObject& movingObj) {
	if (!m_wallTaken) return Direction::STAND;
	else return Direction::DOWN;
}
