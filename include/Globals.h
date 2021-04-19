#pragma once


//************************************** GLOBALS FOR THE PROGRAM ***********************************//
class StaticObject;
enum Globals { HEIGHT = 700, WIDTH = 1000, NUM_OF_BUTTONS = 3, BUTTON_RADIUS = 65};

enum class Objects { PLAYER = '@', ENEMY = '%', WALL = '#', LADDER = 'H', POLE = '-', GIFT = '+', COIN = '*', AIR = ' ' };

enum Statics{ WALL_S, LADDER_S, POLE_S, COIN_S, GIFT_S};

enum class Direction{ UP, RIGHT, DOWN, LEFT, STAND, PICK_GIFT};

const std::string FILE_NAME = "Board.txt";
const int LIFES = 3;

enum class ToolBar{ TOOLBAR_HEIGHT = 80, TOOLBAR_WIDTH = 1000};

enum class MovingObjectPart{LEGS, HEAD, BODY, RIGHT_SIDE, LEFT_SIDE};

struct AdjacentStaticObjects {
	StaticObject* objToLeft = nullptr;
	StaticObject* objToRight = nullptr;
	StaticObject* objToAbove = nullptr;
	StaticObject* objToBelow = nullptr;
	StaticObject* currObj = nullptr;
};

const std::vector<std::string> STRINGS = { "Level: ", "Lifes: ", "Score: ", "Time Left: ", "Your Score is: ", "Next Level is: ", "Infinity" };

const int PLAYER_DEFAULT_VELOCITY = 200;
const int ENEMY_DEFAULT_VELOCITY = 125;

const int LIFE_VALUE_GIFT = 1;
const int TIME_VALUE_GIFT = 10;
const int MAX_TIME = 3;