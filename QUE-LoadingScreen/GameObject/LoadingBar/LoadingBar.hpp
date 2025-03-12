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
	void updateProgress();

private:
	sf::Time updateTime;
	sf::Text* progressText;
	int framesPassed = 0;



};

