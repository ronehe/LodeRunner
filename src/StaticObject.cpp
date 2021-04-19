#include <StaticObject.h>

void StaticObject::reset()
{
	return;
}


Direction StaticObject::direction_if_on_this_object(MovingObject&) {

	return Direction::STAND;
}

Direction StaticObject::direction_if_above_this_object(MovingObject&) {

	return Direction::STAND;
}
