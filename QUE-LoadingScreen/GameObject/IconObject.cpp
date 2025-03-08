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
	//assign texture
	sf::Texture* texture = TextureManager::getInstance()->getBaseTextureFromList(this->textureIndex);
	this->sprite = new sf::Sprite(*texture);
}

void IconObject::processInput(sf::Event event)
{
}

void IconObject::update(sf::Time deltaTime)
{
}

void IconObject::draw(sf::RenderWindow* targetWindow)
{
    if (!this->sprite) return;

    const sf::Texture& texture = this->sprite->getTexture();

    sf::Vector2f position = this->getPosition();
    sf::Vector2u texSize = texture.getSize();
    float width = static_cast<float>(texSize.x);
    float height = static_cast<float>(texSize.y);

    sf::Vertex vertices[6];

    vertices[0].position = sf::Vector2f(position.x, position.y);
    vertices[0].texCoords = sf::Vector2f(0, 0);
    vertices[0].color = sf::Color(255, 255, 255, 100); 

    vertices[1].position = sf::Vector2f(position.x + width, position.y);
    vertices[1].texCoords = sf::Vector2f(width, 0);
    vertices[1].color = sf::Color(255, 255, 255, 100); 

    vertices[2].position = sf::Vector2f(position.x, position.y + height);
    vertices[2].texCoords = sf::Vector2f(0, height);
    vertices[2].color = sf::Color(255, 255, 255, 255); 

    vertices[3].position = sf::Vector2f(position.x, position.y + height);
    vertices[3].texCoords = sf::Vector2f(0, height);
    vertices[3].color = sf::Color(255, 255, 255, 255); 

    vertices[4].position = sf::Vector2f(position.x + width, position.y);
    vertices[4].texCoords = sf::Vector2f(width, 0);
    vertices[4].color = sf::Color(255, 255, 255, 100); 

    vertices[5].position = sf::Vector2f(position.x + width, position.y + height);
    vertices[5].texCoords = sf::Vector2f(width, height);
    vertices[5].color = sf::Color(255, 255, 255, 255); 

    sf::RenderStates states;
    states.texture = &texture;

    targetWindow->draw(vertices, 6, sf::PrimitiveType::Triangles, states);
}



