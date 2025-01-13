#pragma once
#include "AGameObject.h"

class GameObjectManager
{
private:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;
	GameObjectManager& operator=(GameObjectManager&&) = delete;

public:
	static void initialize();
	static GameObjectManager* getInstance();

private:
	static GameObjectManager* sharedInstance;

public:
	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllObjects();
	int activeObjects();

	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);

	void addObject(AGameObject* gameObject);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);

private:
	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;
};

