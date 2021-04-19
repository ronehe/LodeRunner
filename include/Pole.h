#pragma once
#include <MovingObject.h>
#include <StaticObject.h>

class Pole : public StaticObject {
public:
	using StaticObject::StaticObject;
	Direction direction_if_above_this_object(MovingObject&) override;

private:
};