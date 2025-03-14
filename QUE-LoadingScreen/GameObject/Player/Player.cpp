#include "Player.h"

#include "../../Texture/TextureManager.h"

#include "../../Settings.h"
#include "../../AssetLoader/SFXManager.h"

Player::Player() : AGameObject("Player")
{
}

Player::~Player()
{
    this->texture = nullptr;
    this->texture2 = nullptr;

    delete this->sprite;
}

void Player::initialize()
{
	this->texture = TextureManager::getInstance()->getFromTextureMap("CatOhm", 0);
    this->texture2 = TextureManager::getInstance()->getFromTextureMap("CatAhh", 0);

	this->sprite = new sf::Sprite(*texture);

    sf::FloatRect globalBounds = sprite->getGlobalBounds();
    sf::Vector2f size = globalBounds.size;
    this->sprite->setOrigin({ size.x / 2, size.y / 2 });

    this->setScale(0.2, 0.2);
	this->setPosition(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 2);
}


void Player::update(sf::Time deltaTime)
{
    float deltaSeconds = deltaTime.asSeconds();

	sf::FloatRect globalBounds = sprite->getGlobalBounds();
	sf::Vector2f size = globalBounds.size;

	if (!dead)
    {
        velocityY += gravity * deltaSeconds;
        posY += velocityY * deltaSeconds;

        if (posY - size.y / 2 < 0)
        {
            posY = size.y / 2;
            velocityY = 0;
        }

        if (posY + size.y / 2 >= WINDOW_HEIGHT)
        {
            posY = WINDOW_HEIGHT - size.y / 2; 
            velocityY = 0;
            dead = true;

            SFXManager::getInstance()->getSound(SFXType::DIE)->play();

            elapsedTime = sf::Time::Zero;
        }

        this->setPosition(posX, posY);
    }

    else 
    {
        elapsedTime += deltaTime;

        if (elapsedTime.asSeconds() >= 0.2f)
        {
            this->dead = false;
            this->elapsedTime = sf::Time::Zero;

            if (this->posY + size.y / 2 >= WINDOW_HEIGHT)
				this->setPosition(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 2);

            velocityY = 0;
        }
    }
}


void Player::processInput(sf::Event event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        onKeyDown(keyPressed->scancode);
    }

    if (const auto* keyPressed = event.getIf<sf::Event::KeyReleased>())
    {
        onKeyUp(keyPressed->scancode);
    }
}

void Player::onKeyDown(sf::Keyboard::Scancode key)
{
    if (key == sf::Keyboard::Scancode::Space && canJump)
    {
        velocityY = jumpForce;
        canJump = false;

        this->sprite->setTexture(*texture2);

        SFXManager::getInstance()->getSound(SFXType::POP)->play();
    }
}

void Player::onKeyUp(sf::Keyboard::Scancode key)
{
    if (key == sf::Keyboard::Scancode::Space)
    {
        canJump = true;

        this->sprite->setTexture(*texture);
    }
}

bool Player::isDead()
{
    return this->dead;
}

void Player::setDead(bool dead)
{
    this->dead = dead;
}