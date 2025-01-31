#pragma once

#include "AGameObject.h"

class IconObject : public AGameObject
{
public:
	IconObject(std::string name, int textureIndex);

public:
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	int textureIndex = 0;
};

