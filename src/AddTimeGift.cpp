#include "AddTimeGift.h"


void AddTimeGift::handleCollision(Player* player) {
	if(!m_isTaken) player->addTime(m_value);
	Gift::handleCollision(player);
}
