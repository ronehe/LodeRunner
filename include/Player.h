#pragma once
#include <SFML/Graphics.hpp>
#include "MovingObject.h"
#include "Wall.h"
#include "Pole.h"

class Wall;
class Coin;
class Pole;
class StaticObject;
class ConstEnemy;
class AddLifeGift;
class AddScoreGift;

class Player : public MovingObject {
private:
	int m_lifes;
	int m_score = 0;
	int m_time;
	bool m_addTime = false;
	bool m_addScore = false;
	bool m_addLife = false;
	sf::Sound m_meepMeep;
public:
	void setDirection();
	Player(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const float& speed, const Direction& direcation, const int& playerLifes, const int& playerScore);
	int getLifes() const;
	int getScore() const;
	void addScore(const int&);
	void addLife(const int&);
	void addTime(const int&);
	void setScore(const int& currentScore);
	void setTime(const int&);
	int getTime() const;
	void move(const float& deltatime);
	int getDefaultVelocity();
	void die();
	sf::Vector2f getPosition() const;
	void handleSpecialKeys(Board*);
	void dig(Wall*);
	bool lostGame() const;
	void handleCollision(GameObject*) override;
	void meepMeep();
};
