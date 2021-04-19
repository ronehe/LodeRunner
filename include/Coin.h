#pragma once
#include "StaticObject.h"

class Board;
class Coin : public StaticObject {
public:
	Coin(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const int&);
	~Coin();
	void draw(sf::RenderWindow&) override;
	void remove();
	void reset() override;
	void handleCollision(Player* player) override;
	static void setCoins(const int&);
	static int getNumCoins();
private:
	int m_value;
	static int m_num_of_coins;
	bool m_isTaken = false;
};
