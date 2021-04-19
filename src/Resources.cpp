#include "Resources.h"
#include <iostream>

std::vector<sf::Texture> Resources::m_enemyTextures;
std::vector<sf::Texture> Resources::m_playerTextures;
std::vector<sf::Texture> Resources::m_staticTextures;
std::vector<sf::Texture> Resources::m_menuTextures;
std::vector<sf::Texture> Resources::m_levelsTexture;
std::vector<sf::Texture*> Resources::m_tempTexCpy;
std::vector<sf::SoundBuffer> Resources::m_soundBuffers;
std::vector<sf::Font> Resources::m_fonts;
std::vector<sf::Font*> Resources::m_tempFontCpy;
std::vector<sf::SoundBuffer*> Resources::m_tempSoundCpy;
std::vector<sf::Music*> m_tempMusics;


Resources::Resources() {

	m_fonts.resize(1);
	m_fonts[0].loadFromFile("FFF_Tusj.ttf");

	m_soundBuffers.resize(6);
	m_soundBuffers[0].loadFromFile("MenuButton.wav");
	m_soundBuffers[1].loadFromFile("GameOver.wav");
	m_soundBuffers[2].loadFromFile("Meep Meep.wav");
	m_soundBuffers[3].loadFromFile("Ending.wav");
	m_soundBuffers[4].loadFromFile("DingDong.wav");
	m_soundBuffers[5].loadFromFile("Champions.wav");
	
	// Menu textures
	m_menuTextures.resize(8);
	m_menuTextures[0].loadFromFile("Menu.png");
	m_menuTextures[1].loadFromFile("startButton.png");
	m_menuTextures[2].loadFromFile("ExitButton.png");
	m_menuTextures[3].loadFromFile("MuteButton.png");
	m_menuTextures[4].loadFromFile("UpMenu.png");
	m_menuTextures[5].loadFromFile("EndingGame.png");
	m_menuTextures[6].loadFromFile("YouWin.png");
	m_menuTextures[7].loadFromFile("emptyRed.png");
	for (auto i = 0; i < m_menuTextures.size(); i++)
		m_menuTextures[i].setSmooth(true);

	// Levels textures
	m_levelsTexture.resize(4);
	m_levelsTexture[0].loadFromFile("Stage1.png");
	m_levelsTexture[1].loadFromFile("GameOver.png");
	m_levelsTexture[2].loadFromFile("TryAgain.png");
	m_levelsTexture[3].loadFromFile("Ready.png");
	for (auto i = 0; i < m_levelsTexture.size(); i++)
		m_levelsTexture[i].setSmooth(true);

	// Player animations
	m_playerTextures.resize(3);
	m_playerTextures[0].loadFromFile("PlayerStand.png");
	m_playerTextures[1].loadFromFile("PlayerRun.png");
	m_playerTextures[2].loadFromFile("PlayerHoldGift.png");
	for (auto i = 0; i < m_playerTextures.size(); i++)
		m_playerTextures[i].setSmooth(true);

	// Enemy animations
	m_enemyTextures.resize(2);
	m_enemyTextures[0].loadFromFile("EnemyStand.png");
	m_enemyTextures[1].loadFromFile("EnemyRun.png");
	for (auto i = 0; i < m_enemyTextures.size(); i++)
		m_enemyTextures[i].setSmooth(true);

	// Static textures
	m_staticTextures.resize(5);
	m_staticTextures[WALL_S].loadFromFile("Wall.png");
	m_staticTextures[LADDER_S].loadFromFile("Ladder.png");
	m_staticTextures[POLE_S].loadFromFile("Pole.png");
	m_staticTextures[COIN_S].loadFromFile("Coin.png");
	m_staticTextures[GIFT_S].loadFromFile("Gift.png");
	for (auto i = 0; i < m_staticTextures.size(); i++)
		m_staticTextures[i].setSmooth(true);


}

Resources& Resources::getInstance()
{
	static Resources instance;
	return instance;
}

//******************* I USED DEEP COPY FOR ALL THE TEXTURE/SOUNDBUFFER AND ETC *******************//
sf::Texture* Resources::getPlayerTexture(const int& index) const
{
	sf::Texture* p2Texture = new sf::Texture(m_playerTextures[index]);
	m_tempTexCpy.push_back(p2Texture);

	return p2Texture;
}

sf::Texture* Resources::getEnemyTexture(const int& index) const
{
	sf::Texture* p2Texture = new sf::Texture(m_enemyTextures[index]);
	m_tempTexCpy.push_back(p2Texture);

	return p2Texture;
}

sf::Texture* Resources::getStaticTexture(const int& index) const
{
	sf::Texture* p2Texture = new sf::Texture(m_staticTextures[index]);
	m_tempTexCpy.push_back(p2Texture);

	return p2Texture;
}

sf::Texture* Resources::getMenuTexture(const int& index) const
{
	sf::Texture* p2Texture = new sf::Texture(m_menuTextures[index]);
	m_tempTexCpy.push_back(p2Texture);

	return p2Texture;
}

sf::Texture* Resources::getLevelTexture(const int& index) const
{
	sf::Texture* p2Texture = new sf::Texture(m_levelsTexture[index]);
	m_tempTexCpy.push_back(p2Texture);

	return p2Texture;
}

sf::SoundBuffer* Resources::getSoundBuffer(const int& index) const
{
	sf::SoundBuffer* p2Buffer = new sf::SoundBuffer(m_soundBuffers[index]);
	m_tempSoundCpy.push_back(p2Buffer);

	return p2Buffer;
}

sf::Font* Resources::getFont(const int& index) const
{
	sf::Font* p2Font = new sf::Font(m_fonts[index]);
	m_tempFontCpy.push_back(p2Font);

	return p2Font;
}

//	Free all the allocated memories
Resources::~Resources()
{
	for (auto i = 0; i < m_tempFontCpy.size(); i++)
		delete m_tempFontCpy[i];

	for (auto i = 0; i < m_tempSoundCpy.size(); i++)
		delete m_tempSoundCpy[i];

	for (auto i = 0; i < m_tempTexCpy.size(); i++)
		delete m_tempTexCpy[i];
}
