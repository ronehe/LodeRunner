#pragma once

#include <GameObject.h>

class Board;
class StaticObject : public GameObject {
public:
	using GameObject::GameObject;
	virtual Direction direction_if_on_this_object(MovingObject&);
	virtual Direction direction_if_above_this_object(MovingObject&);
	virtual void reset();
private:
};