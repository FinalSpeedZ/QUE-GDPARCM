#include "BGObject.h"

#include "Constants.h"
#include "TextureManager.h"

BGObject::BGObject(std::string name)
	: AGameObject(name)
{
}

void BGObject::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	texture->setRepeated(true);

	this->sprite = new sf::Sprite(*texture);
	std::cout << "BG object successful" << std::endl;

	sf::Vector2u textureSize = this->sprite->getTexture().getSize();

	this->sprite->setTextureRect(sf::IntRect({0, 0}, {WINDOW_WIDTH, WINDOW_HEIGHT * 8}));
	this->setPosition(0, -WINDOW_HEIGHT * 7);
}

void BGObject::processInput(sf::Event event)
{
}

void BGObject::update(sf::Time deltaTime)
{
	sf::Vector2f position = this->getPosition();

	position.y += BG_SPEED * deltaTime.asSeconds();

	this->setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite->getPosition();

	if (localPos.y * deltaTime.asSeconds() > 0)
	{
		this->setPosition(0, -WINDOW_HEIGHT * 7);
	}


}
