#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

private:
	AGameObject(const AGameObject&) = delete;
	AGameObject(AGameObject&&) = delete;
	AGameObject& operator=(const AGameObject&) = delete;
	AGameObject& operator=(AGameObject&&) = delete;

public:
	virtual void initialize() = 0;
	virtual void processInput(sf::Event event) = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderWindow* targetWindow);

	std::string getName();

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

	virtual sf::FloatRect getLocalBounds();

protected:
	std::string name;

	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;

	float posX = 0.0f;
	float posY = 0.0f;

	float scaleX = 1.0f;
	float scaleY = 1.0f;
};

