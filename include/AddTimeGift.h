#pragma once
#include "GoodGift.h"
#include "MovingObject.h"


class AddTimeGift : public GoodGift {
public:
	using GoodGift::GoodGift;
	void handleCollision(Player* player);
private:
};