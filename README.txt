README: PROJECT
==============================================
Written by: 
Ronen Heifetz, id: 316481423
Oz Shurki, id:308015205


GENERAL INFORMATION
====================================================

we developed a game with the same rules as Lode Runner.
The game creates a game out of a text file containing the file using pre-defined symbols
to indicate certain objects, such as walls, ladders, poles, player and enemies.

The general idea behind the development is changing the initial text file with the given 
information into a matrix of pointers of objects that is the main source if interaction between the
objects of this game.
This way lets us determine adjacant objects to every object we desire - which simplifies calculations of collisions

This way the adjacant objects of every moving object can be addressed directly while they are updated
constantly. This way, we can deduce the surroundings of every object at every time and do operations 
accordingly of object and its surroundings.

we decided that upon losing a level, everything is resetted, including the timer, score, life, coins and gifts.

when digging a hole in a floor and there is no floor underneath, the player stays
in the hole as though as there was a floor underneath

DESIGN
=====================================================
We have created the following objects for this program:

BASE OBJECTS:
--------------------

GAME MASTER:
	this class ties every single object in this game together. it is responsible for handling the base
	of the game - it creates the board, and is responsible for showing the windows and making actions
	depending on the current state of the game.

BOARD:
	this is the main class that handles directly with everything related to the actual game.
	this class creates the necessary objects according to the text file and displays them on the screen,
	such as the matrix map, enemies, and the player.

RESOURCES:
	this class is responsible for creating every single outside source of information
	that the game uses - such as textures and sounds. it is essentially a singleton
	so it is possible for other object to access it directly

MENU:
	this class is responsible for handling the pre-game menu, it has 3 buttons
	available, in order to start game, exit or shut music.

GAME OBJECTS
---------------------

GAME OBJECT:
	this is the base class of every single object that is game-related. every property of this object
	is a shared property of every single object of the game. 

MOVING OBJECT:
	this is the base class of every moving object in the game, essentially, this class represents
	all characters.
 
STATIC OBJECT:
	this is the base class of all static object. it is the type of the map, so every moving object
	can know which static objects are adjacant to it.

PLAYER:
	this class represents the player. the player has a certain score and number of lifes left.
	the player is a private member of the board, and it gets generated and destroyed at the beginning
	and at the end of each level.

ENEMY:
	this class represents the enemy. its whole purpose is to kill the enemy. they are stored in the board
	as a vector for easy access for all at the same time.

SMART ENEMY:
	this class represents the smart enemy. this enemy has an access to the position of the player
	and uses an algorithm to set its direction accordingly to get directly to player

CONST ENEMY:
	this class represents another type of enemy which moves only left and right, and upon collision
	or reaching an edge of the floor, he changes direction.

DUMB ENEMY:
	this class represents an enemy that moves in random direction.

WALL:
	this is a static object that represents an object which no moving object can be on.
	it serves as both a wall and a floor. 
	all moving object use this object to deduce if they are on a valid location, and act accordingly.
	the default of every moving object is if it not on top of a wall, it needs to be dropped
	unless he is on another valid location.
	the wall can be dug and removed using special operation of the player - in this case
	every moving object found inside the generated hole is moved up on top of the returned
	floor.

LADDER:
	the ladder is the object used by moving object to move up and down. a moving obejct is
	considered to be on a valid location if it is on a wall.

POLE:
	the pole is the object used by moving objects to move left and right while not being 
	on top of floor. it is a valid location for every moving object to be on.

COIN:
	the coin is the main way the player can increase his score. each coin is assigned with a value
	upon creation, and depending on number of level, and upon collision with it, the score
	increases accordingly.
	when a player dies, if the board resets, all the coins are returned to their original locations
	and can be taken again. the score resets as well.

GIFT:
	the gift is a base class. it serves as a base for all objects that have an affect on the situation of the 
	board or player, besides the coin. 

GOODGIFT:
	this is a base class for all gifts that have an affect on the player. 

ADDLIFEGIFT:
	this is a class for gifts that add life. they have an associated value of life that the player
	collides will it gets this much amount of life.

ADDTIMEGIFT:
	essentially the same as ADDLIFEGIFT but adds time instead

ADDSCOREGIFT:
	essentially the same as ADDLIFEGIFT but adds score instead

BADGIFT:
	this gift is a bad gift, it has a pointer to the board, and upon collision with player - it 
	calls for a function to the board to create an additional enemy

LEVEL FORMAT
====================================
	to add additional levels, you can add another one on Board.txt
	in resources directory, and putting in at the desired level.
	
	note you need to put rows, columns, and time at the beginning
	with a newline seperating between two levels.
	at the end there is supposed to be no newline.


SELF GENERATED FILES
===========================================

all the files below are the code and header for the project.

AddLifeGift.cpp 		AddLifeGift.h:
AddScoreGift.cpp		AddScoreGift.h
AddTimeGift.cpp		AddTimeGift.h	
BadGift.cpp		BadGift.h
Board.cpp		Board.h	
Button.cpp		Button.h
Coin.cpp			Coin.h
ConstEnemy.cpp		ConstEnemy.h
DumbEnemy.cpp		DumbEnemy.h
Enemy.cpp		Enemy.h
GameMaster.cpp		GameMaster.h
GameObject.cpp		GameObject.h
Gift.cpp			Gift.h
GoodGift.cpp		GoodGift.h
Ladder.cpp		Ladder.h
main.cpp			
Menu.cpp		Menu.h
MovingObject.cpp		MovingObject.h
Player.cpp		Player.h
Pole.cpp			Pole.h
Resources.cpp		Resourcrs.h
SmartEnemy.cpp		SmartEnemy.h
StaticObject.cpp		StaticObject.h
Wall.cpp			Wall.h

there are also included all the music and textures used in the game in the Resoureces directory.

DATA STRUCTURES
==============================================
	the main data structure used is the matrix of ptrs of GameObject to indicate
	the surroundings of every object in the game.

	a singleton is also used in order to maintain outside information such as textures and sounds.

NOTEWORTHY ALGORITHMS:
==========================================

SmartEnemyAlgorithm:
	the smart enemy uses a special algorithm that go to the player in the x axis,
	and once he has reached to the same x axis as the player and is on a ladder, he goes
	up or down depending on where the player is relatively to the enemy

Finding Position In Matrix:
	each sprite has its own position relatively to the window. we use
	the property that every object has the same size to conclude what are the correct row and column
	if they were on the matrix of static objects. we find the position in the x/y axis by the height/width 
	accordingly. this gives us the necessary information, meaning the row and column of the object
	had they been inside the matrix. this conclusion lets us know directly what are
	the adjacent objects of every given object.

KNOWN BUGS
=======================================
	the or enemy are able to climb on coins and gifts after they were taken
	when the window of TryAgain shows you need to move the mouse

CHANGES SINCE PRESENTATION
==========================================
	the player is now a member of board
	