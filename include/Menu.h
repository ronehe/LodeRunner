#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include <Globals.h>
#include <SFML\Audio\Music.hpp>
#include "Resources.h"


class Menu {
public:
	Menu();
	void runMenu(sf::RenderWindow& window);

private:
	void makeButtons();
	void drawButtons(sf::RenderWindow&);
	void setTextures();
	void handelMouseOver(sf::RenderWindow& win, const sf::Event::MouseMoveEvent& event);
	bool handelClicking(sf::RenderWindow& window, sf::Music& music, const sf::Vector2f& location, bool& musicOn);
	void muteMusic(bool& musicOn);
	void endingWindow(sf::RenderWindow&);

	std::vector<sf::Sprite> m_sprites;
	std::vector<Button> m_buttons;
	sf::Music m_music;
	std::vector<sf::Sound> m_sounds;
};