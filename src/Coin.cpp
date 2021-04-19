#include <Coin.h>
#include <Board.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

int Coin::m_num_of_coins = 0;

Coin::Coin(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const int& value) :
	StaticObject(tex, pos, size), m_value(value) {
	int i = 3;
	m_num_of_coins++;
}

Coin::~Coin()
{
	m_num_of_coins = 0;
}

int Coin::getNumCoins() {
	return m_num_of_coins;
}

void Coin::reset() {

	if (m_isTaken) {
		m_isTaken = false;
		m_num_of_coins++;
	}
	else
		return;
}

void Coin::draw(sf::RenderWindow& window) {

	if (!m_isTaken)
		window.draw(m_sprite);
}

// Mark the coin to taken
void Coin::remove() {

	m_num_of_coins--;
	m_isTaken = true;
}

void Coin::handleCollision(Player* player) {

	if (!m_isTaken) {
		player->addScore(m_value);
		this->remove();
		player->meepMeep();
	}
}

void Coin::setCoins(const int& num)
{
	m_num_of_coins = num;
}
