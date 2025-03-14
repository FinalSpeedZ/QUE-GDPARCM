#include "AppWindow.h"

#include "../AssetLoader/SFXManager.h"
#include "../GameObject/GameObjectManager.h"
#include "../GameObject/FPSCounter/FPSCounter.h"
#include "../Texture/TextureManager.h"
#include "../AssetLoader/VideoDisplay.h"
#include "../GameObject/BGObject.h"
#include "../GameObject/LoadingBar/LoadingBar.hpp"
#include "../GameObject/Pipes/Pipes.h"
#include "../GameObject/Player/Player.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
	: window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "QUE-Loading-Screen", sf::Style::None)
{
	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	GameObjectManager::initialize();
	TextureManager::initialize();
	SFXManager::initialize();

	// Loading Screen
	BGObject* flappyBG = new BGObject("FlappyBG");
	GameObjectManager::getInstance()->addObject(flappyBG);

	Player* player = new Player();
	GameObjectManager::getInstance()->addObject(player);

	Pipes* pipes = new Pipes();
	GameObjectManager::getInstance()->addObject(pipes);

	LoadingBar* loadingBar = new LoadingBar();
	GameObjectManager::getInstance()->addObject(loadingBar);

	FPSCounter* fpsCounter = new FPSCounter();
	fpsCounter->initialize();
	GameObjectManager::getInstance()->setFPSCounter(fpsCounter);
}

void AppWindow::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			update(elapsedTime);
		}

		draw();
	}
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::processEvents()
{
	while (const std::optional<sf::Event> event = this->window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			this->window.close();
		}

		else
		{
			GameObjectManager::getInstance()->processInput(*event);
		}
	}
}

void AppWindow::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
}

void AppWindow::draw()
{
	this->window.clear();

	GameObjectManager::getInstance()->draw(&this->window);

	this->window.display();
}
