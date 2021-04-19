#include "AddLifeGift.h"

void AddLifeGift::handleCollision(Player* player) {
	if(!m_isTaken) player->addLife(m_value);
	Gift::handleCollision(player);
}
