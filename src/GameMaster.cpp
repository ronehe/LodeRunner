#include "GameMaster.h"
#include <iostream>

GameMaster::GameMaster()
	: m_window(sf::VideoMode(WIDTH, HEIGHT), "Menu"), m_numOfLevel(0), m_currentLevel(1)
{
	Resources& r = Resources::getInstance();

	m_music.openFromFile("LevelSound.ogg");
	m_champions.setBuffer(*r.getSoundBuffer(5));
	m_champions.setVolume(50);
}

void GameMaster::run()
{
	Resources& r = Resources::getInstance();
	auto currentScore = 0;
	auto playerLifes = LIFES;
	
	m_menu.runMenu(m_window);
	m_window.clear();
	m_currentLevel = 1;

	while (1) {
		m_board.printLevel(m_currentLevel, playerLifes, currentScore);	// Create all the objects from file
		startLevel(m_window, playerLifes, currentScore);				// Start the level
		currentScore = currentScore + m_currentLevel * 50;
		m_currentLevel++;
	}
}

void GameMaster::startLevel(sf::RenderWindow& window, int& playerLifes, int& playerScore)
{
	bool musicOn = true;
	auto timer = m_board.getPlayerTime();

	sf::Clock clock;
	sf::Clock time;
	sf::Sprite backGround;
	Resources& r = Resources::getInstance();

	musicHandler();
	m_board.setCurrentLevel(m_currentLevel);
	backGround.setTexture(*r.getLevelTexture(0));
	

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_board.closeFile();
				window.close();
			}
		}

		float deltaTime = clock.restart().asSeconds();
		updateTimer(timer, time);	// Update the time left

		m_board.handleMovingObjects(deltaTime);

		if (event.type == sf::Event::MouseButtonReleased)
			handleMouse(event, musicOn);

		if (Coin::getNumCoins() == 0) {
			if (m_board.isEOF())
				GameFinished(m_board.getPlayerScore());	// You complete the game
			tempWindow(r.getLevelTexture(3), STRINGS[5], sf::Vector2f(0.6f, 0.5f), m_currentLevel + 1, MAX_TIME);
			break;
		}

		if (m_board.isGameOver())	// Player is dead
			gameOver(m_window);
			
		if (m_board.ifReset() || timer == 0) {	// Reset the level
			if (timer < 0){
				m_resetScore = true;
				m_board.killPlayer();
			}
			handleReset(clock,time);
			 timer = m_board.getPlayerTime();
		}

		window.clear();
		window.draw(backGround);
		m_board.draw(m_window);
		m_board.drawLevelData(m_window, m_currentLevel, m_board.getPlayerLife(), m_board.getPlayerScore(), timer);	// Draw the details of the level
		window.display();
	}

	playerLifes = m_board.getPlayerLife();
	playerScore = m_board.getPlayerScore();
	m_board.clearDataStructure();	// Clear all the vectors for the next round
	window.clear();
	window.display();
}

void GameMaster::gameOver(sf::RenderWindow& window)
{
	Resources& r = Resources::getInstance();

	sf::Sound gameOver;
	sf::Clock timer;
	int maxTime = MAX_TIME + 2;
	int timeLeft;
	m_music.stop();
	gameOver.setBuffer(*r.getSoundBuffer(1));
	gameOver.setLoop(false);
	gameOver.play();

	m_window.clear();
	m_backGround.setTexture(*r.getLevelTexture(1));
	m_backGround.scale(0.84f, 0.82f);
	window.draw(m_backGround);
	window.display();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				m_board.closeFile();
				window.close();
			}
		}
		timeLeft = maxTime - timer.getElapsedTime().asSeconds();
		if (timeLeft < 0) {
			m_window.clear();
			m_board.clearDataStructure();
			m_board.closeFile();
			run();	// Start the game again
		}
	}
}
// If player hit enemy
void GameMaster::tryAgain()
{
	m_window.clear();
	m_music.stop();
	Resources& r = Resources::getInstance();

	int maxTime = MAX_TIME+2;
	int timeLeft;

	sf::Sprite backGround;
	sf::Clock timer;
	sf::Text text;
	std::string str = STRINGS[3];

	text.setFont(*r.getFont(0));
	text.setColor(sf::Color::Red);
	text.setPosition(WIDTH / 2, HEIGHT - 100);
	text.setCharacterSize(50);

	backGround.setTexture(*r.getLevelTexture(2));
	backGround.setScale(2.0f, 1.2f);
	m_window.display();

	while (m_window.isOpen()) {
		sf::Event event;

		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_board.closeFile();
				m_window.close();
			}
		}
		timeLeft = maxTime - timer.getElapsedTime().asSeconds();
		str.append(std::to_string(timeLeft));
		text.setString(str);

		m_window.draw(backGround);
		m_window.draw(text);

		if (timeLeft < 0) {
			m_window.clear();
			return;
		}

		str = "";
		m_window.display();
		m_window.clear();
	}
}

void GameMaster::musicHandler()
{
	m_music.play();
	m_music.setVolume(10);
	m_music.setLoop(true);
}

// If the user clicked on mute button
void GameMaster::handelClicking(sf::RenderWindow& win, const sf::Vector2f& location, bool& musicOn)
{
	if (m_board.getMuteBtn().getSprite().getGlobalBounds().contains(location))
		muteMusic(musicOn);
}

void GameMaster::muteMusic(bool& musicOn)
{
	if (musicOn == true) {
		musicOn = false;
		m_music.stop();
	}
	else {
		musicOn = true;
		m_music.play();
	}
}

void GameMaster::tempWindow(const sf::Texture* texture, std::string str, const sf::Vector2f& size, const int& number, const int& maxTime)
{
	m_music.stop();
	m_window.clear();
	Resources& r = Resources::getInstance();

	sf::Text text;
	sf::Clock timer;
	sf::Vector2f postion(0, HEIGHT - 100);

	int timeLeft;

	text.setFont(*r.getFont(0));
	text.setPosition(WIDTH / 3, HEIGHT - 100);
	text.setCharacterSize(50);
	str.append(std::to_string(number));
	text.setString(str);

	m_backGround.setTexture(*texture, true);
	m_backGround.setScale(size);

	while (m_window.isOpen()) {
		if (auto event = sf::Event{}; m_window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				m_board.closeFile();
				m_window.close();
				exit(1);
			}
			timeLeft = maxTime - timer.getElapsedTime().asSeconds();
			if (timeLeft < 0) {
				m_window.clear();
				m_window.display();
				return;
			}

			m_window.clear();
			m_window.draw(m_backGround);
			m_window.draw(text);
			m_window.display();
		}
	}
}

void GameMaster::handleMouse(sf::Event& event, bool& musicOn)
{
	auto location = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
	if (event.mouseButton.button == sf::Mouse::Button::Left)  // left mouse button released
		handelClicking(m_window, location, musicOn);
}

void GameMaster::handleReset(sf::Clock& clock, sf::Clock& time)
{
	m_board.resetMap(m_resetScore);
	tryAgain();
	m_music.play();
	m_music.setVolume(15);
	time.restart();
	clock.restart();
}

void GameMaster::updateTimer(int& timer, sf::Clock& time)
{
	if (m_board.getPlayerTime() != -1)
		timer = m_board.getPlayerTime() - time.getElapsedTime().asSeconds();
	else
		timer = -1;	// Infinity time
}

void GameMaster::GameFinished(const int& playerScore)
{
	Resources& r = Resources::getInstance();
	auto score = playerScore + m_currentLevel * 50;
	m_window.clear();
	m_window.display();
	m_music.stop();
	m_champions.play();
	tempWindow(r.getMenuTexture(6), STRINGS[4], sf::Vector2f(0.28f, 0.27), playerScore, MAX_TIME+11);
	m_board.clearDataStructure();
	run();
}
