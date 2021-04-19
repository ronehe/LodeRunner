#include "BadGift.h"
#include <Board.h>


BadGift::BadGift(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, Board* board)
	: Gift(tex, pos, size), m_board(board) {}

void BadGift::handleCollision(Player* player)
{


	if (!m_isTaken) m_board->addEnemyToGame();
	Gift::handleCollision(player);
}
