#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Globals.h"

class Resources {
public:
	static Resources& getInstance();
	 sf::Texture* getPlayerTexture(const int&) const;
	 sf::Texture* getEnemyTexture(const int&) const;
	 sf::Texture* getStaticTexture(const int&) const;
	sf::Texture* getMenuTexture(const int&) const;
	sf::Texture* getLevelTexture(const int&) const;
	sf::SoundBuffer* getSoundBuffer(const int&) const;
	sf::Font* getFont(const int&) const;

	~Resources();
	
private:
	Resources();
	
	static std::vector<sf::Texture> m_menuTextures;
	static std::vector<sf::Texture> m_levelsTexture;
	static std::vector<sf::Texture> m_playerTextures;
	static std::vector<sf::Texture> m_enemyTextures;
	static std::vector<sf::Texture> m_staticTextures;
	static std::vector<sf::SoundBuffer> m_soundBuffers;
	static std::vector<sf::Font> m_fonts;
	static std::vector<sf::Texture*> m_tempTexCpy;	// For deep copy
	static std::vector<sf::Font*> m_tempFontCpy;
	static std::vector<sf::SoundBuffer*> m_tempSoundCpy;
	static std::vector<sf::Music*> m_tempMusics;
	
};