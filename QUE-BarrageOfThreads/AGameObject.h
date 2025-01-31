#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class AGameObject : sf::NonCopyable
{

public:
	AGameObject(std::string name);
	~AGameObject();

public:
	virtual void initialize() = 0;

	virtual void processInput(sf::Event event) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow* targetWindow);

	std::string getName();

	virtual sf::Vector2f getPosition();
	virtual void setPosition(float x, float y);

	virtual sf::Vector2f getScale();
	virtual void setScale(float x, float y);

	virtual sf::FloatRect getLocalBounds();

protected:
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;

	float posX = 0.0f;
	float posY = 0.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

