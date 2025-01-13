#pragma once

#include "AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(std::string name);
	~BGObject() = default;

public:
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
};

