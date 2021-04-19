#include "Board.h"
#include "Globals.h"
#include <stdlib.h>
#include <iostream>
#include <experimental/vector>

Board::Board()
	:m_toolbar(sf::Vector2f((float)ToolBar::TOOLBAR_WIDTH, (float)ToolBar::TOOLBAR_HEIGHT))
	, m_muteButton(940.0f, (float)(HEIGHT)-(float)(ToolBar::TOOLBAR_HEIGHT) * 0.75, sf::Vector2f(0.10, 0.10), *Resources::getInstance().getMenuTexture(3)),
	m_eof(false), m_player(*Resources::getInstance().getPlayerTexture(0), sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Vector2f(50, 35), 0.0f, Direction::LEFT, 0, 0)
{
	Resources& r = Resources::getInstance();

	m_file.open(FILE_NAME);
	makeLevelData();	// Make the level details

	m_dingDong.setBuffer(*r.getSoundBuffer(4));
	m_dingDong.setVolume(100);
}

Button Board::getMuteBtn() const
{
	return m_muteButton;
}

void Board::closeFile()
{
	m_file.close();
}

int Board::getPlayerTime() const
{
	return m_player.getTime();
}

int Board::getPlayerLife() const
{
	return m_player.getLifes();
}

int Board::getPlayerScore() const
{
	return m_player.getScore();
}

bool Board::ifReset() const 
{
	return m_player.isObjectDead();
}


bool Board::isEOF() const
{
	return m_eof;
}

void Board::printLevel(const int& numOfLevel, const int& playerLifes, const int& playerScore)
{
	if (!m_file.is_open()) {	// If i want to play the game again
		m_file.open(FILE_NAME);
		m_eof = false;
	}
	m_initial_num_enemies = 0;	// Reset the amount of enemies
	m_coins = 0;	// Reset the amount of coins
	srand(time(NULL));
	Coin::setCoins(0);
	Resources& r = Resources::getInstance();

	char type;
	std::string rowsInput;
	std::string colsInput;
	std::string timeInput;
	std::string lineInMap;

	m_file >> rowsInput >> colsInput >> timeInput;

	auto rows = stoi(rowsInput);
	auto cols = stoi(colsInput);
	auto time = stoi(timeInput);

	m_staticObjects.resize(rows);
	for (auto i = 0; i < rows; i++) m_staticObjects[i].resize(cols);
		m_staticObjectsSize = sf::Vector2u(rows, cols);

	
	auto objctWidth = ((double)WIDTH / cols);
	auto objctHeight = (((double)HEIGHT - (double)ToolBar::TOOLBAR_HEIGHT) / rows);
	sf::Vector2f size(objctWidth, objctHeight);
	sf::Vector2f location(0, 0);

	// Create all the game object direct from file
	for (auto i = 0; i < rows; i++) {
		m_file.get();

		for (auto j = 0; j < cols; j++) {

			auto position = sf::Vector2f(j * objctWidth, i * objctHeight);
			m_file.get(type);
			int enemyType;
			int giftType;

			switch (type) {
			case (char)Objects::PLAYER:
				m_player = Player(*r.getPlayerTexture(0), position, size, 200.0f, Direction::LEFT, playerLifes, playerScore);
				m_player.setTime(time);
				m_staticObjects[i][j] = nullptr;
				break;

			case (char)Objects::ENEMY:
				enemyType = rand() % 3;

				if (enemyType == 0)
					m_enemies.emplace_back(std::make_unique<DumbEnemy>(*r.getEnemyTexture(0), position, size, 50.0f, Direction::LEFT));
				else if (enemyType == 1)
					m_enemies.emplace_back(std::make_unique<ConstEnemy>(*r.getEnemyTexture(0), position, size, 50.0f, Direction::LEFT));
				else if (enemyType == 2)
					m_enemies.emplace_back(std::make_unique<SmartEnemy>(*r.getEnemyTexture(0), position, size, 50.0f, Direction::LEFT, m_player));

				m_staticObjects[i][j] = nullptr;
				m_initial_num_enemies++;
				break;

			case (char)Objects::WALL:
				m_staticObjects[i][j] = std::make_unique<Wall>(*r.getStaticTexture(WALL_S), position, size);
				break;

			case (char)Objects::POLE:
				m_staticObjects[i][j] = std::make_unique<Pole>(*r.getStaticTexture(POLE_S), position, size);
				break;

			case (char)Objects::COIN:
				m_staticObjects[i][j] = std::make_unique<Coin>(*r.getStaticTexture(COIN_S), position, size, 2 * numOfLevel);
				break;

			case (char)Objects::LADDER:
				m_staticObjects[i][j] = std::make_unique<Ladder>(*r.getStaticTexture(LADDER_S), position, size);
				break;

			case (char)Objects::GIFT:
				giftType = rand() % 4;

				if (giftType == 0)
					m_staticObjects[i][j] = std::make_unique<BadGift>(*r.getStaticTexture(GIFT_S), position, size, this);
				else if (giftType == 1)
					m_staticObjects[i][j] = std::make_unique<AddTimeGift>(*r.getStaticTexture(GIFT_S), position, size, TIME_VALUE_GIFT);
				else if (giftType == 2)
					m_staticObjects[i][j] = std::make_unique<AddLifeGift>(*r.getStaticTexture(GIFT_S), position, size, LIFE_VALUE_GIFT);
				else if (giftType == 3)
					m_staticObjects[i][j] = std::make_unique<AddScoreGift>(*r.getStaticTexture(GIFT_S), position, size, numOfLevel*2);
				break;
			default:
				m_staticObjects[i][j] = nullptr;
			}
		}
	}

	m_file.get();
	m_file.get();
	if (m_file.eof()) {	// End of file
		m_eof = true;
		m_file.close();
	}
}
// Draw all objects
void Board::draw(sf::RenderWindow& window)
{
	for (auto i = 0; i < m_staticObjects.size(); i++) {
		for (auto j = 0; j < m_staticObjects[i].size(); j++) {
			if (m_staticObjects[i][j]) m_staticObjects[i][j]->draw(window);
		}
	}

	for (auto i = 0; i < m_enemies.size(); i++) {
		if(dynamic_cast<ConstEnemy*>(m_enemies[i].get())){
			auto i = 3;
		}
		m_enemies[i]->draw(window);
	}

	m_player.draw(window);
}

void Board::makeLevelData()
{
	Resources& r = Resources::getInstance();	// Singlton

	sf::Vector2f postion(0, HEIGHT - ((float)ToolBar::TOOLBAR_HEIGHT));
	m_toolbar.setPosition(postion);
	m_toolbar.setFillColor(sf::Color(255, 204, 102));
	m_toolbar.setOutlineColor(sf::Color::Black);
	m_toolbar.setOutlineThickness(3);

	m_texts.resize(4);
	m_strings.resize(4);

	for (auto i = 0; i < m_texts.size(); i++)
		m_texts[i].setFont(*r.getFont(0));

	m_texts[0].setPosition(sf::Vector2f(10.0f, (float)(HEIGHT)-(float)(ToolBar::TOOLBAR_HEIGHT) * 0.75));
	m_texts[0].setCharacterSize(40);
	m_texts[0].setColor(sf::Color::Black);


	m_texts[1].setPosition(sf::Vector2f(200.0f, (float)(HEIGHT)-(float)(ToolBar::TOOLBAR_HEIGHT) * 0.75));
	m_texts[1].setCharacterSize(40);
	m_texts[1].setColor(sf::Color::Black);


	m_texts[2].setPosition(sf::Vector2f(400.0f, (float)(HEIGHT)-(float)(ToolBar::TOOLBAR_HEIGHT) * 0.75));
	m_texts[2].setCharacterSize(40);
	m_texts[2].setColor(sf::Color::Black);


	m_texts[3].setPosition(sf::Vector2f(600.0f, (float)(HEIGHT)-(float)(ToolBar::TOOLBAR_HEIGHT) * 0.75));
	m_texts[3].setCharacterSize(40);
	m_texts[3].setColor(sf::Color::Black);

}

void Board::drawLevelData(sf::RenderWindow& window, const int& level, const int& lifes, const int& score, const int& time)
{
	Resources& r = Resources::getInstance();
	window.draw(m_toolbar);

	if( time == 10)
		m_dingDong.play();

	if (time < 10 && time > 0) {
		m_texts[3].setCharacterSize(47);
		m_texts[3].setColor(sf::Color::Red);
	}
	else if(time > 10){
		m_texts[3].setCharacterSize(40);
		m_texts[3].setColor(sf::Color::Black);
	}

	m_strings[0] = STRINGS[0];
	m_strings[0].append(std::to_string(level));
	m_strings[1] = STRINGS[1];
	m_strings[1].append(std::to_string(lifes));
	m_strings[2] = STRINGS[2];
	m_strings[2].append(std::to_string(score));
	m_strings[3] = STRINGS[3];
	if (time == -1) {
		m_texts[3].setCharacterSize(35);
		m_texts[3].setFillColor(sf::Color::Blue);
		m_strings[3].append(STRINGS[6]);	// Infinity time
	}
	else
		m_strings[3].append(std::to_string(time));

	for (auto i = 0; i < m_texts.size(); i++) {
		m_texts[i].setString(m_strings[i]);
		window.draw(m_texts[i]);
	}
	window.draw(m_muteButton.getSprite());
}

// Point to the objects around the MovingObject
void Board::updateAdjacentStaticObjects(MovingObject& movingObj) {

	auto pos = getPositionOnMap(movingObj, MovingObjectPart::BODY);
	auto pos_legs = getPositionOnMap(movingObj, MovingObjectPart::LEGS);
	StaticObject* left, * right, * up, * down, * curr;
	if (pos.x == 0)	up = nullptr;
	else up = m_staticObjects[pos.x - 1][pos.y].get();

	if (pos_legs.x == m_staticObjectsSize.x) down = nullptr;
	else down = m_staticObjects[pos_legs.x][pos_legs.y].get();

	if (pos.y == 0) left = nullptr;
	else left = m_staticObjects[pos.x][pos.y - 1].get();

	if (pos.y == m_staticObjectsSize.y - 1) right = nullptr;
	else right = m_staticObjects[pos.x][pos.y + (unsigned int)1].get();

	curr = m_staticObjects[pos.x][pos.y].get();
	movingObj.updateAdjacentObjects(left, right, up, down, curr);
}

Wall* Board::getFloorToLeft() {
	auto pos = getPositionOnMap(m_player, MovingObjectPart::BODY);
	if (pos.x != 0 && pos.y != m_staticObjectsSize.y)
		return dynamic_cast<Wall*>(m_staticObjects[pos.x + 1][pos.y - 1].get());
	return nullptr;
}

Wall* Board::getFloorToRight() {
	auto pos = getPositionOnMap(m_player, MovingObjectPart::BODY);
	if (pos.x != m_staticObjectsSize.x && pos.y != m_staticObjectsSize.y)
		return dynamic_cast<Wall*>(m_staticObjects[pos.x + 1][pos.y + 1].get());
	return nullptr;
}

void Board::resetMap(const bool& resetScore) {

	if (resetScore)
		m_player.setScore(0);

	m_player.resetPosition();
	for (auto i = 0; i < m_enemies.size(); i++)
		m_enemies[i].get()->resetPosition();

	for (auto i = 0; i < m_staticObjects.size(); i++) {
		for (auto j = 0; j < m_staticObjects[i].size(); j++) {
			if(m_staticObjects[i][j]) m_staticObjects[i][j].get()->reset();
		}
	}

	//release all other enemies
	auto num_of_enemies = Enemy::getTotalNumEnemies();
	for (auto i = m_initial_num_enemies; i < m_enemies.size(); i++)
		m_enemies[i].release(); //release only new enemies created from bad gift
	m_enemies.erase(m_enemies.begin() + m_initial_num_enemies, m_enemies.end());
}

void Board::clearDataStructure()
{

	m_enemies.clear();
	for (auto i = 0; i < m_staticObjects.size(); i++)
		m_staticObjects[i].clear();
	m_staticObjects.clear();
}

void Board::setCurrentLevel(const int& level)
{
	m_currenLevel = level;
}

void Board::addEnemyToGame()
{
	Resources& r = Resources::getInstance();
	auto objctWidth = ((double)WIDTH / m_staticObjectsSize.y);
	auto objctHeight = (((double)HEIGHT - (double)ToolBar::TOOLBAR_HEIGHT) / m_staticObjectsSize.x);
	sf::Vector2f position;

	for(auto i = 0; i<m_staticObjectsSize.x; i++)
		for (auto j = 0; j < m_staticObjectsSize.y; j++) {
			if (m_staticObjects[i][j] == nullptr)
				 position = sf::Vector2f(j * objctWidth, i * objctHeight);
		}
	sf::Vector2f size(objctWidth, objctHeight);

	auto randomEnemy = rand() % 3;
	switch (randomEnemy) {
	case 0:
		m_enemies.emplace_back(std::make_unique<DumbEnemy>(*r.getEnemyTexture(0), position, size, 100.0f, Direction::LEFT));
		break;
	case 1:
		m_enemies.emplace_back(std::make_unique<ConstEnemy>(*r.getEnemyTexture(0), position, size, 100.0f, Direction::LEFT));
		break;
	case 2:
		m_enemies.emplace_back(std::make_unique<SmartEnemy>(*r.getEnemyTexture(0), position, size, 100.0f, Direction::LEFT, m_player));
	}
}

// Check if the movingObjects inside the window
bool Board::insideBoard(MovingObject* object)
{
	auto position_center = getPositionOnMap(*object, MovingObjectPart::BODY);
	auto position_left = getPositionOnMap(*object, MovingObjectPart::LEFT_SIDE);
	auto position_right = getPositionOnMap(*object, MovingObjectPart::RIGHT_SIDE);
	auto position_head = getPositionOnMap(*object, MovingObjectPart::HEAD);
	auto position_legs = getPositionOnMap(*object, MovingObjectPart::LEGS);

	if (position_right.y == 0 ||
		position_left.y == m_staticObjectsSize.y ||
		position_head.x == m_staticObjectsSize.x ||
		position_legs.x == 0)
		return false;
	else
		return true;
}
// Calculate the position relatively to the staticsObjects matrix
sf::Vector2u Board::getPositionOnMap(GameObject& gameObj, MovingObjectPart part) {

	auto rect = gameObj.getShapeGlobalBounds();
	auto rectCenter = sf::Vector2f();

	if (part == MovingObjectPart::BODY)
		rectCenter = sf::Vector2f(rect.left + rect.width / 2 , rect.top + rect.height / 2);

	else if (part == MovingObjectPart::LEGS)
		rectCenter = sf::Vector2f(rect.left + rect.width / 2, rect.top + rect.height);

	else if (part == MovingObjectPart::LEFT_SIDE)
		rectCenter = sf::Vector2f(rect.left, rect.top + rect.height / 2);

	else if (part == MovingObjectPart::RIGHT_SIDE)
		rectCenter = sf::Vector2f(rect.left + rect.width, rect.top + rect.height / 2);

	else rectCenter = sf::Vector2f(rect.left + rect.width / 2, rect.top);

	auto pos = sf::Vector2u(int(rectCenter.y / rect.height), int(rectCenter.x / rect.width));
	return pos;
}

bool Board::isGameOver() const {
	return m_player.lostGame();
}

void Board::killPlayer() {
	m_player.die();
}

void Board::handleMovingObjects(const float& deltaTime)
{
	moveObject(&m_player, deltaTime);
	m_player.handleSpecialKeys(this);

	for (auto i = 0; i < m_enemies.size(); i++) {
		if (i == 0)
			auto k = 0;
		moveObject(m_enemies[i].get(), deltaTime);

		if (m_player.collision(*m_enemies[i]))
			m_enemies[i]->kill(m_player);
	}
}
// Generic function for each moving object
void Board::moveObject(MovingObject* object, const float& deltaTime) {

	Direction direction;
	Resources& r = Resources::getInstance();
	auto position = object->getPosition();

	this->updateAdjacentStaticObjects(*object);
	object->setDirection();

	if (auto ptrToObject = object->collision())
		object->handleCollision(ptrToObject);
	
	object->move(deltaTime);

	if (!insideBoard(object))
		object->setPosition(position);
	
}