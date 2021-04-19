#include <GameObject.h>
#include <iostream>

GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	:m_size(size)
{
		m_sprite.setTexture(texture, true);

	updateSprite(pos, size);	// reuse for the sprite details
}


void GameObject::updateSprite(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	m_sprite.setOrigin(this->getShapeGlobalBounds().width / 2, this->getShapeGlobalBounds().height / 2);
	m_sprite.setScale(1 / m_sprite.getGlobalBounds().width * size.x, 1 / m_sprite.getGlobalBounds().height * size.y);
	m_size = m_sprite.getScale();
	m_sprite.setPosition(sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2 + 1));
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void GameObject::setAnimation(const Direction& direction, const sf::Texture& texture)
{
	if (direction == Direction::RIGHT) {
		m_sprite.setTexture(texture, true);	// Running texture
		m_sprite.setScale({ m_size.x,m_size.y });
	}
	else if (direction == Direction::LEFT) {
		m_sprite.setTexture(texture, true);	// Running texture
		m_sprite.setScale({ -m_size.x,m_size.y });
	}
	else
		m_sprite.setTexture(texture, true);	// Standing texture
}

sf::FloatRect GameObject::getShapeGlobalBounds() {

	return (sf::FloatRect)m_sprite.getGlobalBounds();
}

void GameObject::setSprite(sf::Texture* texture) {

	m_sprite.setTexture(*texture);
}

sf::Vector2f GameObject::getScale() const
{
	return m_sprite.getScale();
}

sf::Vector2f GameObject::getSize() const
{
	return m_size;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::setPosition(const sf::Vector2f& newpos) {

	m_sprite.setPosition(newpos);
}

void GameObject::handleCollision(GameObject*) {
	return;
}

void GameObject::handleCollision(Player*) {
	return;
}
void GameObject::handleCollision(Enemy*) {
	return;
}
void GameObject::handleCollision(Coin*) {
	return;
}

void GameObject::handleCollision(AddScoreGift*) {
	return;
}
void GameObject::handleCollision(AddLifeGift*) {
	return;
}
void GameObject::handleCollision(AddTimeGift*) {
	return;
}
