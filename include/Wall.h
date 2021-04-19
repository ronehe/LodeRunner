#pragma once
#include <StaticObject.h>
#include <MovingObject.h>
#include "Player.h"
#include "Enemy.h"

class Board;
class Player;

class Wall : public StaticObject {
private:
	sf::Clock m_timer;
	bool m_wallTaken = false;
public:
	using StaticObject::StaticObject;
	void handleCollision(Player*) override;
	void handleCollision(Enemy*);
	void draw(sf::RenderWindow& window) override;
	void remove();

	Direction direction_if_on_this_object(MovingObject&) override;
	Direction direction_if_above_this_object(MovingObject&) override;
};
