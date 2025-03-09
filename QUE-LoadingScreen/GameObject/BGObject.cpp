#include "BGObject.h"

#include "../Settings.h"
#include "../Texture/TextureManager.h"

BGObject::BGObject(std::string name)
	: AGameObject(name)
{
}

void BGObject::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("BackgroundBG", 0);
	texture->setRepeated(true);

	this->sprite = new sf::Sprite(*texture);

	sf::Vector2u textureSize = this->sprite->getTexture().getSize();

	this->sprite->setTextureRect(sf::IntRect({ 0, 0 }, { WINDOW_WIDTH, WINDOW_HEIGHT }));
}

void BGObject::processInput(sf::Event event)
{
}

void BGObject::update(sf::Time deltaTime)
{
}
