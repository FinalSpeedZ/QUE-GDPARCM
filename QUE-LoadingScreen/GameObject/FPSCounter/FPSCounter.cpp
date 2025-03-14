#include "FPSCounter.h"

#include "../../Settings.h"

FPSCounter::FPSCounter() : AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->openFromFile("../Media/Sansation.ttf");

	this->statsText = new sf::Text(*font);
	this->statsText->setPosition({ WINDOW_WIDTH - 200, 20 });
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(50);
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	this->updateTime += elapsedTime;

	if (this->updateTime >= sf::seconds(0.5f))
	{
		float fps = 1.0f / elapsedTime.asSeconds();

		this->statsText->setString("FPS: " + std::to_string(static_cast<int>(fps)));
		this->updateTime = sf::seconds(0.0f);
	}
}
