#include <Gift.h>

void Gift::reset() {
	m_isTaken = false;
}

void Gift::draw(sf::RenderWindow& window) {
	if(!m_isTaken) window.draw(m_sprite);
}

void Gift::handleCollision(Player* player) {
	if (!m_isTaken) player->meepMeep();
	m_isTaken = true;
}
