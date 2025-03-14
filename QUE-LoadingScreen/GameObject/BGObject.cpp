#include "BGObject.h"

#include "GameObjectManager.h"
#include "../Settings.h"
#include "../Texture/TextureManager.h"

#include "../AssetLoader/VideoDisplay.h"

class VideoDisplay;

BGObject::BGObject(std::string name)
    : AGameObject(name), fadeAlpha(255), fading(false) 
{
}

void BGObject::initialize()
{
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, 0);

    std::cout << name << std::endl;

    texture->setRepeated(true);

    this->sprite = new sf::Sprite(*texture);
    sf::Vector2u textureSize = this->sprite->getTexture().getSize();
    this->sprite->setTextureRect(sf::IntRect({ 0, 0 }, { WINDOW_WIDTH, WINDOW_HEIGHT }));

    if (name == "FlappyBG")
    {
        this->sprite2 = new sf::Sprite(*texture);
        this->sprite2->setTextureRect(sf::IntRect({ 0, 0 }, { WINDOW_WIDTH, WINDOW_HEIGHT }));

        this->sprite->setPosition({ 0, 0 });
        this->sprite2->setPosition({ WINDOW_WIDTH - 5, 0 });
    }
}

void BGObject::update(sf::Time deltaTime)
{
    if (name == "FlappyBG")
    {
        float deltaX = -100 * deltaTime.asSeconds();

        this->sprite->setPosition({ this->sprite->getPosition().x + deltaX, 0 });
        this->sprite2->setPosition({ this->sprite2->getPosition().x + deltaX, 0 });

        float x1 = this->sprite->getPosition().x;
        float x2 = this->sprite2->getPosition().x;

        if (x1 <= -WINDOW_WIDTH + 5)
        {
            this->sprite->setPosition({ WINDOW_WIDTH - 5, 0 });
        }

        if (x2 <= -WINDOW_WIDTH + 5)
        {
            this->sprite2->setPosition({ WINDOW_WIDTH - 5, 0 });
        }
    }
}

void BGObject::draw(sf::RenderWindow* targetWindow)
{
    if (name == "FlappyBG")
    {
        this->sprite->setColor(sf::Color(255, 255, 255, fadeAlpha)); 
        this->sprite2->setColor(sf::Color(255, 255, 255, fadeAlpha));

        targetWindow->draw(*this->sprite);
        targetWindow->draw(*this->sprite2);
    }
    else if (name == "VideoBG")
    {
        targetWindow->draw(*this->sprite);
    }
}