#pragma once

#include "AGameObject.h"

class FPSCounter : public AGameObject
{
public:
	FPSCounter();
	~FPSCounter();

public:
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	void updateFPS(sf::Time elapsedTime);

private:
	sf::Time updateTime;
	sf::Text* statsText;
	int framesPassed = 0;



};

