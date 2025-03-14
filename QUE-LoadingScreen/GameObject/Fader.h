#pragma once

#include "AGameObject.h"

class Fader : public AGameObject
{
public:
	Fader(std::string name = "Fader");
	~Fader() override;

	void initialize() override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	int fadeAlpha = 0;
	bool fading = false;
	bool unfading = false;

	sf::RectangleShape fadeRect;
};

