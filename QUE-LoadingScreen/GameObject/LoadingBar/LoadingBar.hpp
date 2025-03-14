#pragma once

#include "../AGameObject.h"

class LoadingBar : public AGameObject
{
public:
	LoadingBar();
	~LoadingBar();

public:
	void initialize() override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	int framesPassed = 0;
	sf::Time elapsedTime = sf::Time::Zero;
};

