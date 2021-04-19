#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Menu.h"
#include "Board.h"
#include <time.h>
#include "Button.h"

// tempWindow is a generic function to display win or between levels window
class GameMaster{
public:
	GameMaster();
	void run();

private:
	void startLevel(sf::RenderWindow& window, int& playerLifes, int& playerScore);
	void gameOver(sf::RenderWindow& window);	
	void tryAgain();
	void musicHandler();
	void handelClicking(sf::RenderWindow&, const sf::Vector2f& , bool& );
	void muteMusic(bool&);
	void tempWindow(const sf::Texture*, std::string str, const sf::Vector2f& size, const int& number, const int&);
	void handleMouse(sf::Event&, bool&);
	void handleReset(sf::Clock& clock, sf::Clock& time);
	void updateTimer(int&, sf::Clock&);
	void GameFinished(const int&);

	sf::Music m_music;
	sf::Sound m_champions;
	sf::RenderWindow m_window;
	Menu m_menu;
	Board m_board;
	sf::Sprite m_backGround;
	int m_currentLevel;
	int m_numOfLevel;
	bool m_resetScore = false;
};