#include "Fader.h"

#include "BGObject.h"
#include "GameObjectManager.h"

#include "../AssetLoader/VideoDisplay.h"

#include "../Settings.h"

class VideoDisplay;

Fader::Fader(std::string name) : AGameObject(name)
{
	this->fadeRect.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	this->fadeRect.setFillColor(sf::Color(0, 0, 0, fadeAlpha));

    this->fading = true;
    this->unfading = false;
}

Fader::~Fader()
{
}

void Fader::initialize()
{
}

void Fader::update(sf::Time deltaTime)
{
    if (fading && !unfading)
    {
        fadeAlpha += static_cast<int>(100 * deltaTime.asSeconds());
        if (fadeAlpha >= 255)
        {
            fadeAlpha = 255;
            fading = false;

            GameObjectManager::getInstance()->deleteObjectByName("Pipes");
            GameObjectManager::getInstance()->deleteObjectByName("Player");
            GameObjectManager::getInstance()->deleteObjectByName("LoadingBar");
            GameObjectManager::getInstance()->deleteObjectByName("FlappyBG");

            unfading = true; 
        }
        fadeRect.setFillColor(sf::Color(0, 0, 0, fadeAlpha));
    }

    else if (unfading && name == "Fader")
    {
        fadeAlpha -= static_cast<int>(500 * deltaTime.asSeconds());
        if (fadeAlpha <= 0)
        {
            fadeAlpha = 0;
            unfading = false;
				
            VideoDisplay* textureDisplay = new VideoDisplay();
            GameObjectManager::getInstance()->addObject(textureDisplay);
        }
        fadeRect.setFillColor(sf::Color(0, 0, 0, fadeAlpha));
    }
}

void Fader::draw(sf::RenderWindow* targetWindow)
{
    targetWindow->draw(fadeRect);
}
