#pragma once
#include "GameObject.h"

class MovingObject : public GameObject {
public:
	MovingObject(const sf::Texture&, const sf::Vector2f&, const sf::Vector2f&, const float&, const Direction&);
	virtual void move(const float& deltaTime);
	void move(const sf::Vector2f& vec);
	virtual void setDirection()=0;
	Direction defaultDirection();
	GameObject* collision();
	GameObject* collision(MovingObject&);
	void resetPosition();
	sf::Vector2f getStartLoc() const;
	Direction drop();
	void stand();
	virtual void updateAdjacentObjects(
		StaticObject* left,
		StaticObject* right,
		StaticObject* up,
		StaticObject* down,
		StaticObject* curr);
	void updateVelocity();
	virtual int getDefaultVelocity() = 0;
	virtual void die();
	bool isObjectDead() const;

protected:
	Direction m_direction;
	sf::Vector2f m_startLocation;

private:
	AdjacentStaticObjects adjacentStaticObjects;
	float m_velocity;
	float m_speed;
	bool isFalling = false;
	bool isDead = false;
	sf::Vector2f getDirectionVector(const Direction&) const;
};