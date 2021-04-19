#include <MovingObject.h>
#include <iostream>
#include <StaticObject.h>
#include <Wall.h>

MovingObject::MovingObject(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& size, const float& speed, const Direction& direction) :
	GameObject(tex, pos, size), m_speed(speed), m_velocity(speed), m_direction(Direction::STAND) {

	m_startLocation = m_sprite.getPosition();
}

void MovingObject::move(const float& deltaTime)
{
	auto direction = getDirectionVector(m_direction);	// delete
	auto directionVector = getDirectionVector(m_direction);
	m_sprite.move(directionVector * m_velocity * deltaTime);
}

void MovingObject::move(const sf::Vector2f& vec) {
	m_sprite.move(vec);
}


sf::Vector2f MovingObject::getDirectionVector(const Direction& direction) const{
	if (direction == Direction::RIGHT) return sf::Vector2f(1, 0);
	if (direction == Direction::LEFT) return sf::Vector2f(-1, 0);
	if (direction == Direction::UP) return sf::Vector2f(0, -1);
	if (direction == Direction::DOWN) return sf::Vector2f(0, 1);
	else return sf::Vector2f(0, 0);
}

//function that checks collision
/*
this function checks if there is an intersection
it checks if there is an intersecting point between the middle points of each length of moving object
with any object possible.

we are using side ways instead of points to avoid collision between corners, which might share a point
with 4 different objects
*/

GameObject* MovingObject::collision(MovingObject& movingObj){
	auto obj1 = this->getShapeGlobalBounds();
	auto obj2 = movingObj.getShapeGlobalBounds();
	if (obj1.intersects(obj2)) return &movingObj;
	else return nullptr;
}
GameObject* MovingObject::collision() {
	sf::FloatRect rectMove = this->getShapeGlobalBounds();
	sf::FloatRect rectObj;

	//if left, check if something to the left
	if (m_direction == Direction::LEFT) {
		if (!adjacentStaticObjects.objToLeft) return nullptr;
		rectObj = adjacentStaticObjects.objToLeft->getShapeGlobalBounds();
		if(rectObj.intersects(rectMove))
			return adjacentStaticObjects.objToLeft;
	}
	//if right, check if something to the right
	else if (m_direction == Direction::RIGHT) {
		if (!adjacentStaticObjects.objToRight) return nullptr;
		rectObj = adjacentStaticObjects.objToRight->getShapeGlobalBounds();
		if(rectObj.intersects(rectMove))
			return adjacentStaticObjects.objToRight;
	}
	//if up, check if something above
	else if (m_direction == Direction::DOWN) {
		if (!adjacentStaticObjects.objToBelow) return nullptr;
		rectObj = adjacentStaticObjects.objToBelow->getShapeGlobalBounds();
		if(rectObj.intersects(rectMove))
			return adjacentStaticObjects.objToBelow;
	}
	//if down, check if something below
	else if (m_direction == Direction::UP) {
		if (!adjacentStaticObjects.objToAbove) return nullptr; 
		rectObj = adjacentStaticObjects.objToAbove->getShapeGlobalBounds();
		if(rectObj.intersects(rectMove))
			return adjacentStaticObjects.objToAbove;
	}
	return nullptr;
}

void MovingObject::resetPosition()
{
	isDead = false;
	m_sprite.setPosition(m_startLocation);
}

bool MovingObject::isObjectDead() const {
	return isDead;
}

Direction MovingObject::defaultDirection() {

	if (!adjacentStaticObjects.currObj && !adjacentStaticObjects.objToBelow) {
		return Direction::DOWN;
	}
	if (adjacentStaticObjects.currObj) {
		auto direction_if_on_this_object = adjacentStaticObjects.currObj->direction_if_on_this_object(*this);
		if (direction_if_on_this_object != Direction::STAND)
			return direction_if_on_this_object;
	}
	if (adjacentStaticObjects.objToBelow) {
		auto direction_if_above_this_object = adjacentStaticObjects.objToBelow->direction_if_above_this_object(*this);
		if (direction_if_above_this_object != Direction::STAND);
			return direction_if_above_this_object;
	}
	return Direction::STAND;
}
//default of not being on a valid location is to drop until a valid location is found

sf::Vector2f MovingObject::getStartLoc() const
{
	return m_startLocation;
}

Direction MovingObject::drop() {

	setAnimation(Direction::DOWN, *Resources::getInstance().getPlayerTexture(0));
	m_direction = Direction::DOWN;
	if (!isFalling) {
		isFalling = true;
		m_timer.restart();
	}
	m_velocity = 700 * m_timer.getElapsedTime().asSeconds();
	return Direction::DOWN;
}

void MovingObject::stand() {

	setAnimation(Direction::STAND, *Resources::getInstance().getPlayerTexture(0));
	m_direction = Direction::STAND;
}

void MovingObject::die()
{
	isDead = true;
}

void MovingObject::updateAdjacentObjects(
	StaticObject* left,
	StaticObject* right,
	StaticObject* up,
	StaticObject* down,
	StaticObject* curr) {
	this->adjacentStaticObjects.objToAbove= up;
	this->adjacentStaticObjects.objToBelow = down;
	this->adjacentStaticObjects.objToLeft = left;
	this->adjacentStaticObjects.objToRight = right;
	this->adjacentStaticObjects.currObj = curr;
}
