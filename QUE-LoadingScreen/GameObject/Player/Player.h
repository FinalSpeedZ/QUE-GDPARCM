#pragma once

#include "../AGameObject.h"

class Player : public AGameObject
{
public:
	Player();
	~Player() override;

	void initialize() override;
	void update(sf::Time deltaTime) override;
	void processInput(sf::Event event) override;

	void onKeyDown(const sf::Keyboard::Scancode key);
	void onKeyUp(const sf::Keyboard::Scancode key);

	bool isDead();
	void setDead(bool dead);

private:
	float moveSpeed = 0.5f;

	float velocityY;
	const float gravity = 1000.0f;  
	const float jumpForce = -450.0f;

	bool canJump = true;
	bool dead = false;

	sf::Texture* texture2 = nullptr;
};