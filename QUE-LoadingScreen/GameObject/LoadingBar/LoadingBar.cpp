#include "LoadingBar.hpp"

#include "../../Settings.h"
#include "../../Texture/TextureManager.h"

LoadingBar::LoadingBar() : AGameObject("LoadingBar")
{
}

LoadingBar::~LoadingBar()
{
	delete this->progressText;
	AGameObject::~AGameObject();
}

void LoadingBar::initialize()
{
	sf::Font* font = new sf::Font();
	font->openFromFile("../Media/Sansation.ttf");

	this->progressText = new sf::Text(*font);
	this->progressText->setPosition({ WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT - 100});
	this->progressText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->progressText->setOutlineThickness(2.5f);
	this->progressText->setCharacterSize(50);
}

void LoadingBar::update(sf::Time deltaTime)
{
	this->updateProgress();

}

void LoadingBar::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->progressText != nullptr)
		targetWindow->draw(*this->progressText);
}


void LoadingBar::updateProgress()
{
	this->progressText->setString("Loading: " + std::to_string(static_cast<int>(TextureManager::getInstance()->getNumLoadedBaseTextures() * 100 / NUM_FRAMES)));

}

