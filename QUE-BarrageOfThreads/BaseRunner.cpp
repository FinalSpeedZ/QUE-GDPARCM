#include "BaseRunner.h"

#include <iostream>

#include  "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "QUE-BarrageOfThreads", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run()
{
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	sf::Time threadSpawnTimer;

	int totalThreadsAdded = 1000; // Initial 1000 threads
	addThreads(1000);

	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;

		// Add threads every 3 seconds until a total of 5000
		if (threadSpawnTimer.asSeconds() >= 3.0f && totalThreadsAdded < 5000) {
			addThreads(500);
			totalThreadsAdded += 500;
			threadSpawnTimer -= sf::seconds(3.0f);  // Reset the timer
		}

		threadSpawnTimer += sf::seconds(deltaTime); // Update thread timer
	}
}

void BaseRunner::addThreads(int num)
{
	std::vector<std::thread> threads;

	for (int i = 0; i < num; ++i)
	{
		std::thread([this, i]() { this->threadWorker(i); }).detach();
	}
}

void BaseRunner::threadWorker(int id)
{
	volatile long long sum = 0;

	for (long long i = 0; i < 100000000; ++i) 
	{
		sum += i; // Arbitrary computation to use CPU
	}

	//std::cout << "Thread " << id << " completed with sum = " << sum << "\n";
}

BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}

float BaseRunner::getFPS() const
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}