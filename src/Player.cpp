#pragma once
#include "Player.h"
#include <iostream>
#include <Coin.h>
#include <Board.h>
#include <StaticObject.h>

#include <AddScoreGift.h>

Player::Player(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const float& speed, const Direction& direcation, const int& playerLifes, const int& playerScore)
	:MovingObject(tex, pos, size, speed, direcation), m_lifes(playerLifes), m_score(playerScore), m_time(0) {

	m_meepMeep.setBuffer(*Resources::getInstance().getSoundBuffer(2));
}


void Player::setDirection()
{
	auto defaultDirection = MovingObject::defaultDirection();

	if (defaultDirection != Direction::STAND) {
		m_direction = defaultDirection;
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		m_direction = Direction::LEFT;
			return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		m_direction = Direction::UP;
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		m_direction = Direction::RIGHT;
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		m_direction = Direction::DOWN;
		return;
	}
	else{
		m_direction = Direction::STAND;
		return;
	}
}

void Player::move(const float& deltaTime) {
	sf::Texture* tex;
	(m_direction == Direction::RIGHT || m_direction == Direction::LEFT) ?
		(tex = Resources::getInstance().getPlayerTexture(1)) :
		(tex = Resources::getInstance().getPlayerTexture(0));
	setAnimation(m_direction, *tex);
	MovingObject::move(deltaTime);
}


int Player::getLifes() const
{
	return m_lifes;
}

int Player::getScore() const
{
	return m_score;
}

bool Player::lostGame() const
{
	return (m_lifes == 0);
}

void Player::addScore(const int& value)
{
	m_score += value;
}

void Player::addLife(const int& life) 
{
	m_lifes += life;
}

void Player::addTime(const int& time)
{
	if (m_time == -1)
		return;
	m_time += time;
}

void Player::setScore(const int& currentScore)
{
	m_score = currentScore;
}

void Player::setTime(const int& time)
{
	m_time = time;
}

int Player::getTime() const
{
	return m_time;
}

sf::Vector2f Player::getPosition() const
{
	return m_sprite.getPosition();
}

int Player::getDefaultVelocity() {
	return PLAYER_DEFAULT_VELOCITY;
}

void Player::die() {
	m_lifes--;
	MovingObject::die();
}

// For diggin skill
void Player::handleSpecialKeys(Board* board) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		if(auto floor = board->getFloorToRight())
			dig(floor);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (auto floor = board->getFloorToLeft())
			dig(floor);
	}
}

void Player::dig(Wall* floor) {
	floor->remove();
}

void Player::handleCollision(GameObject* gameObj) {
	gameObj->handleCollision(this);
}

void Player::meepMeep() {
	m_meepMeep.play();
}
