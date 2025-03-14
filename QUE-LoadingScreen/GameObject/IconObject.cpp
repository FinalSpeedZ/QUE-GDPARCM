#include "IconObject.h"

#include <iostream>

#include "../Window/AppWindow.h"
#include "../Texture/TextureManager.h"

IconObject::IconObject(std::string name, int textureIndex) : AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, 0);
	this->sprite = new sf::Sprite(*texture);
}

void IconObject::update(sf::Time deltaTime)
{
}

void IconObject::draw(sf::RenderWindow* targetWindow)
{
    if (!this->sprite) return;

	this->sprite->setPosition(this->getPosition());

    sf::RectangleShape border;
    sf::FloatRect spriteBounds = this->sprite->getGlobalBounds();

    border.setSize(spriteBounds.size + sf::Vector2f(10, 10)); 

    border.setFillColor(sf::Color::White);

    border.setPosition(sf::Vector2f(this->sprite->getPosition().x - 5, this->sprite->getPosition().y - 5));

    targetWindow->draw(border);

    targetWindow->draw(*this->sprite);
}



