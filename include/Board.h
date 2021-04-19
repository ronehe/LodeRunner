#pragma once
#include <fstream>
#include <vector>
#include <memory>
#include <SFML/Audio.hpp>
#include "StaticObject.h"
#include "MovingObject.h"
#include "ConstEnemy.h"
#include "Globals.h"
#include "DumbEnemy.h"
#include "SmartEnemy.h"
#include "Player.h"
#include "Wall.h"
#include "Pole.h"
#include "Gift.h"
#include "AddLifeGift.h"
#include "AddScoreGift.h"
#include "AddTimeGift.h"
#include "BadGift.h"
#include "Ladder.h"
#include "Coin.h"
#include <Resources.h>
#include <Button.h>

class Enemy;

class Board{
public:
	Board();
	bool isEOF() const;
	void printLevel(const int&, const int&, const int&);
	void draw(sf::RenderWindow& window);
	void makeLevelData();
	void drawLevelData(sf::RenderWindow& window, const int& level, const int& lifes, const int& score, const int& time);
	void resetMap( const bool&);
	void clearDataStructure();
	void setCurrentLevel(const int&);
	Wall* getFloorToRight();
	Wall* getFloorToLeft();
	sf::Vector2u getPositionOnMap(GameObject& gameObj, MovingObjectPart);
	void updateAdjacentStaticObjects(MovingObject&);
	Button getMuteBtn() const;
	void closeFile();
	int getPlayerTime() const;
	int getPlayerLife() const;
	int getPlayerScore() const;
	bool ifReset() const;
	bool isGameOver() const;
	void handleMovingObjects(const float&);
	void moveObject(MovingObject*, const float&);
	void addEnemyToGame();
	void killPlayer();
private:

	bool insideBoard(MovingObject*);

	Player m_player;
	std::vector<std::vector<std::unique_ptr<StaticObject>>> m_staticObjects;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	
	sf::Vector2u m_staticObjectsSize;
	sf::RectangleShape m_toolbar;
	sf::Font m_font;
	std::vector<sf::Text> m_texts;
	std::vector<std::string> m_strings;
	std::fstream m_file;
	Button m_muteButton;
	int m_currenLevel;
	bool m_eof;
	int m_coins;
	int m_initial_num_enemies = 0;
	sf::Sound m_dingDong;
};