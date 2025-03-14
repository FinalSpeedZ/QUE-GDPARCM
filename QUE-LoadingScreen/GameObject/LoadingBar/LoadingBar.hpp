#pragma once

#include <SFML/Audio.hpp>

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
	int framesPassed = 0;
	sf::Time elapsedTime = sf::Time::Zero;

	sf::Text* progressText;

	bool fadeOut = false;
	sf::Sound* bgm;

	bool addedFader = false;
};

