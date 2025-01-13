#include "IconObject.h"

#include "TextureManager.h"

IconObject::IconObject(std::string name, int textureIndex)
	: AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	this->sprite = new sf::Sprite(*texture);
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}
