#pragma once

#include <mutex>
#include <unordered_map>
#include <vector>
#include <string>
#include "AGameObject.h"
#include <SFML/Graphics.hpp>


class GameObjectManager
{
public:
	static GameObjectManager* getInstance();

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
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private
	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;

	std::mutex guard;
};

