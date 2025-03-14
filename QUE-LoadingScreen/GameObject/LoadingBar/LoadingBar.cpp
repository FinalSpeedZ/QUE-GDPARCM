#include "LoadingBar.hpp"

#include "../../Settings.h"
#include "../../Texture/TextureManager.h"

LoadingBar::LoadingBar() : AGameObject("LoadingBar")
{
}

LoadingBar::~LoadingBar()
{
}

void LoadingBar::initialize()
{
	this->texture = TextureManager::getInstance()->getFromTextureMap("LoadingPaw", 0);

	this->sprite = new sf::Sprite(*texture);

	this->setScale(0.1, 0.1);
	this->setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 75);
}

void LoadingBar::update(sf::Time deltaTime)
{
	elapsedTime += deltaTime;

	if (static_cast<int>(TextureManager::getInstance()->getNumLoadedBaseTextures() * 100 / NUM_FRAMES == 100))
	{
		this->sprite->setColor(sf::Color(255, 255, 255, 255));
	}

	else if (elapsedTime.asSeconds() > 1.0f)
	{
		bool isVisible = (this->sprite->getColor().a > 0);
		this->sprite->setColor(sf::Color(255, 255, 255, isVisible ? 0 : 255));
		elapsedTime = sf::Time::Zero;  
	}
}

void LoadingBar::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != NULL)
	{
		targetWindow->draw(*this->sprite);
	}
}

