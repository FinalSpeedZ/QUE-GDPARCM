#include "AppWindow.h"

#include "../GameObject/GameObjectManager.h"
#include "../GameObject/FPSCounter/FPSCounter.h"
#include "../Texture/TextureManager.h"
#include "../AssetLoader/VideoDisplay.h"
#include "../GameObject/LoadingBar/LoadingBar.hpp"
#include "../GameObject/Player/Player.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
	: window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "QUE-Loading-Screen", sf::Style::Default)
{
	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	GameObjectManager::initialize();
	TextureManager::initialize();

	LoadingBar* loadingBar = new LoadingBar();
	GameObjectManager::getInstance()->addObject(loadingBar);

	Player* player = new Player();
	GameObjectManager::getInstance()->addObject(player);

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
