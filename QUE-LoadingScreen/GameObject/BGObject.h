#pragma once

#include "AGameObject.h"

class BGObject : public AGameObject
{
public:
	BGObject(std::string name);
	~BGObject() = default;

public:
	void initialize();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* targetWindow) override;

	void startFade();
	bool isFaded();

private:

	sf::Sprite* sprite2 = nullptr;
};

