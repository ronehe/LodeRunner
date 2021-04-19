#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include <Resources.h>


class MovingObject;
class Player;
class Coin;
class Wall;
class Pole;
class Enemy;
class Ladder;
class AddLifeGift;
class AddScoreGift;
class AddTimeGift;
class BadGift;
class SmartEnemy;

class GameObject {
private:
	void updateSprite(const sf::Vector2f& pos, const sf::Vector2f& size);
	char m_type;

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	sf::Clock m_timer;
	
public:
	GameObject(const sf::Texture&, const sf::Vector2f& pos, const sf::Vector2f& size);
	virtual void draw(sf::RenderWindow&);
	sf::FloatRect getShapeGlobalBounds();
	void setAnimation(const Direction& direction, const sf::Texture& texture);
	void setSprite(sf::Texture*);
	sf::Vector2f getScale() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f&);
	virtual void handleCollision(GameObject*);
	virtual void handleCollision(Player*);
	virtual void handleCollision(Enemy* enemy);
	virtual void handleCollision(Coin*);
	virtual void handleCollision(AddScoreGift*);
	virtual void handleCollision(AddTimeGift*);
	virtual void handleCollision(AddLifeGift*);
};
