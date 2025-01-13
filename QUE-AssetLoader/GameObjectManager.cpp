#include "GameObjectManager.h"

#include <stddef.h>
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != NULL) 
	{
		return this->gameObjectMap[name];
	}

	else 
	{
		std::cout << "Object " << name << " not found!";
		return NULL;
	}
}

std::vector<AGameObject*> GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::processInput(sf::Event event)
{
	for (int i = 0; i < this->gameObjectList.size(); i++)
	{
		this->gameObjectList[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		this->gameObjectList[i]->update(deltaTime);
	}
}

void GameObjectManager::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		this->gameObjectList[i]->draw(window);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->gameObjectMap[gameObject->getName()] = gameObject;
	this->gameObjectList.push_back(gameObject);
	this->gameObjectMap[gameObject->getName()]->initialize();
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) 
	{
		if (this->gameObjectList[i] == gameObject)
		{
			index = i;
			break;
		}
	}

	if (index != -1) 
	{
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}
