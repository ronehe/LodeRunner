#pragma once

#include "StaticObject.h"
#include <Player.h>

class Board;

class Gift : public StaticObject {
public:
	using StaticObject::StaticObject;
	void draw(sf::RenderWindow&) override;
	void reset() override;
	void handleCollision(Player* player);
protected:
	bool m_isTaken = false;

};