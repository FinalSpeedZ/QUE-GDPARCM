#include "LoadingBar.hpp"

#include "../../Settings.h"
#include "../../Texture/TextureManager.h"

#include "../../AssetLoader/SFXManager.h"
#include "../../GameObject/Fader.h"
#include "../../GameObject/GameObjectManager.h"

LoadingBar::LoadingBar() : AGameObject("LoadingBar")
{
	this->bgm = SFXManager::getInstance()->getSound(SFXType::BGM);
}

LoadingBar::~LoadingBar()
{
	delete progressText;
}

void LoadingBar::initialize()
{
	sf::Font* font = new sf::Font();
	if (!font->openFromFile("../Media/Sansation.ttf"))
	{
		std::cerr << "Failed to load font!\n";
		delete font;
		return;
	}

	this->bgm->play();

	this->progressText = new sf::Text(*font, "0%");
	this->progressText->setFillColor(sf::Color::Black);
	this->progressText->setOutlineColor(sf::Color::White);
	this->progressText->setOutlineThickness(1.0f);
	this->progressText->setCharacterSize(23);
	this->progressText->setPosition({ WINDOW_WIDTH - 68, WINDOW_HEIGHT - 45});

	sf::FloatRect textBounds = this->progressText->getLocalBounds();
	this->progressText->setOrigin(textBounds.getCenter());

	this->texture = TextureManager::getInstance()->getFromTextureMap("LoadingPaw", 0);
	this->sprite = new sf::Sprite(*texture);

	this->setScale(0.15f, 0.15f);
	this->setPosition(WINDOW_WIDTH - 120, WINDOW_HEIGHT - 120);
}

void LoadingBar::update(sf::Time deltaTime)
{
	elapsedTime += deltaTime;

	int progress = static_cast<int>((TextureManager::getInstance()->getNumLoadedBaseTextures() * 100.0f) / NUM_FRAMES);

	if (progress == 100)
	{
		progress = 99;

		SFXManager::getInstance()->getSound(SFXType::DIE)->setVolume(0);
		SFXManager::getInstance()->getSound(SFXType::POP)->setVolume(0);
		SFXManager::getInstance()->getSound(SFXType::POINT)->setVolume(0);

		if (!addedFader)
		{	
			Fader* fader = new Fader();
			GameObjectManager::getInstance()->addObject(fader);
			addedFader = true;
		}
	}

	if (progress == 99)
	{
		float currentVolume = bgm->getVolume();
		float newVolume = std::max(0.0f, currentVolume - (deltaTime.asSeconds() * 25.0f));
		bgm->setVolume(newVolume);

		if (newVolume <= 0.0f)
		{
			bgm->stop(); 
		}
	}

	progressText->setString(std::to_string(progress) + "%");
}

void LoadingBar::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != nullptr)
	{
		targetWindow->draw(*this->sprite);
		targetWindow->draw(*progressText);
	}
}
