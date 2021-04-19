#include <Menu.h>

Menu::Menu()
{
	Resources& r = Resources::getInstance();

	m_music.openFromFile("MenuSound.ogg");
	m_music.setVolume(25);
	m_sounds.resize(3);
	m_sounds[0].setBuffer(*r.getSoundBuffer(0));
	m_sounds[1].setBuffer(*r.getSoundBuffer(1));
	m_sounds[2].setBuffer(*r.getSoundBuffer(3));
}

void Menu::runMenu(sf::RenderWindow& window)
{
	Resources& r = Resources::getInstance();
	bool musicOn = true;

	setTextures();
	makeButtons();

	m_music.play();
	m_music.setLoop(true);

	while (window.isOpen()) {

		if (auto event = sf::Event{}; window.waitEvent(event)) {

			switch (event.type) {

			case sf::Event::Closed:	// Pressed close
				m_music.stop();
				window.close();
				break;

			case sf::Event::KeyReleased:

				if (sf::Keyboard::Key::M == event.key.code)	// mute sound
					muteMusic(musicOn);

				if (sf::Keyboard::Key::Escape == event.key.code) {	// pressed escape
					m_music.stop();
					exit(1);
				}
				break;

			case sf::Event::MouseMoved:
				handelMouseOver(window, event.mouseMove);
				break;

			case sf::Event::MouseButtonReleased:
				auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				if (event.mouseButton.button == sf::Mouse::Button::Left)  // left button released
					if (handelClicking(window, m_music, location, musicOn))
						return;
				break;
			}
			window.draw(m_sprites[0]);
			window.draw(m_sprites[4]);
			drawButtons(window);
			window.display();
		}
	}
}

void Menu::makeButtons()
{
	Resources& r = Resources::getInstance();

	for (auto i = 1; i <= NUM_OF_BUTTONS; i++)
		m_buttons.push_back(Button((float)(WIDTH - i * 110), (float)(30), sf::Vector2f(0.15,0.15), *r.getMenuTexture(i)));
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	for (auto i = 0; i < m_buttons.size(); i++)
		window.draw(m_buttons[i].getSprite());
}

void Menu::setTextures()
{
	Resources& r = Resources::getInstance();

	for (auto i = 0; i < 6; i++) {
		sf::Sprite sprite;
		sprite.setTexture(*r.getMenuTexture(i), true);
		m_sprites.push_back(sprite);
	}
	
	m_sprites[0].setPosition(0, 180);
	m_sprites[0].setScale(0.6f, 0.5f);

	m_sprites[4].setScale(0.5f, 0.175f);
}

void Menu::handelMouseOver(sf::RenderWindow& win, const sf::Event::MouseMoveEvent& event)
{
	for (auto i = 0; i < NUM_OF_BUTTONS; i++)
		if (m_buttons[i].getSprite().getGlobalBounds().contains(win.mapPixelToCoords({ event.x,event.y }))) {
			m_buttons[i].setColor(sf::Color::Blue);
			m_sounds[0].play();
		}
		else
			m_buttons[i].setColor(sf::Color::White);
}

bool Menu::handelClicking(sf::RenderWindow& window, sf::Music& music, const sf::Vector2f& location, bool& musicOn)
{
	Resources& r = Resources::getInstance();

	for (auto buttonIndex = 0; buttonIndex < NUM_OF_BUTTONS; buttonIndex++) {

		if (m_buttons[buttonIndex].getSprite().getGlobalBounds().contains(location)) {
			switch (buttonIndex) {
			case 0:
				m_music.stop();
				return true;
				break;
			case 1:
				m_music.stop();
				endingWindow(window);
				break;
			case 2:
				muteMusic(musicOn);
			}
		}
	}
	return false;
}

void Menu::muteMusic(bool& musicOn)
{
	Resources& r = Resources::getInstance();
	
	if (musicOn == true) {
		musicOn = false;
		m_music.stop();
	}
	else {
		musicOn = true;
		m_music.play();
	}
}

void Menu::endingWindow(sf::RenderWindow& window)
{
	Resources& r = Resources::getInstance();
	sf::Clock timer;
	auto maxTime = 9;
	int time;
	window.clear();
	sf::Sprite backGround;
	backGround.setTexture(*r.getMenuTexture(5));
	backGround.setScale(1.5f, 1.5f);
	m_sounds[2].play();

	while (window.isOpen()) {
		window.draw(backGround);
		window.display();
		if (auto event = sf::Event{}; window.pollEvent(event)) {
		}
		time = maxTime - timer.getElapsedTime().asSeconds();
		if(time == 0){
			m_sounds[2].stop();
			window.close();
		}
	}

}


