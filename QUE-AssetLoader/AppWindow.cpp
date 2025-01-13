#include "AppWindow.h"

#include "BGObject.h"
#include "FPSCounter.h"
#include "GameObjectManager.h"
#include "TextureDisplay.h"
#include "TextureManager.h"

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow() 
	: window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "QUE-Asset-Loader", sf::Style::Default)
{
	this->window.setFramerateLimit(int(FRAME_RATE));

	TextureManager::initialize();
	GameObjectManager::initialize();

	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

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
