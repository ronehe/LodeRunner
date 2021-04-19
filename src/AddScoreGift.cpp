#include "AddScoreGift.h"




void AddScoreGift::handleCollision(Player* player) {
	if(!m_isTaken) player->addScore(m_value);
	Gift::handleCollision(player);
}
