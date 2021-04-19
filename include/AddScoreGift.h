#pragma once
#include "GoodGift.h"
#include "MovingObject.h"
#include "StaticObject.h"


class AddScoreGift : public GoodGift {
public:
	using GoodGift::GoodGift;
	void handleCollision(Player*);
private:
};