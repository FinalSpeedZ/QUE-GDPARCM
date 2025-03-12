#include "Player.h"

#include "../../Texture/TextureManager.h"

#include "../../Settings.h"

Player::Player() : AGameObject("Player")
{
}

Player::~Player()
{
}

void Player::initialize()
{
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Player", 0);
	texture->setRepeated(true);

	this->sprite = new sf::Sprite(*texture);

	this->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}


void Player::update(sf::Time deltaTime)
{
    float deltaSeconds = deltaTime.asSeconds();

    sf::FloatRect localBounds = sprite->getLocalBounds();

    sf::Vector2f size = localBounds.size;

    velocityY += gravity * deltaSeconds;

    posY += velocityY * deltaSeconds;

    if (posY < 0)
    {
        posY = 0;
        velocityY = 0;
    }

    if (posY + size.y > WINDOW_HEIGHT)
    {
        posY = WINDOW_HEIGHT - size.y;
        velocityY = 0; 
    }

    this->setPosition(posX, posY);
}

void Player::processInput(sf::Event event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        onKeyDown(keyPressed->scancode);
    }
}

void Player::onKeyDown(sf::Keyboard::Scancode key)
{
    if (key == sf::Keyboard::Scancode::Space)
    {
        velocityY = jumpForce; 
    }
}

