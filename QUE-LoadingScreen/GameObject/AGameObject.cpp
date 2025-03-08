#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	delete this->sprite;
	this->sprite = nullptr;

	delete this->texture;
	this->texture = nullptr;
}

void AGameObject::draw(sf::RenderWindow* targetWindow)
{
	if (this->sprite != NULL)
	{
		this->sprite->setPosition({ this->posX, this->posY });
		this->sprite->setScale({ this->scaleX, this->scaleY });

		targetWindow->draw(*this->sprite);
	}
}

std::string AGameObject::getName()
{
	return this->name;
}

void AGameObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != NULL)
	{
		this->sprite->setPosition({ this->posX, this->posY });
	}
}

void AGameObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != NULL)
	{
		this->sprite->setScale({ this->scaleX, this->scaleY });
	}
}

sf::Vector2f AGameObject::getPosition()
{
	if (this->sprite != NULL)
	{
		return this->sprite->getPosition();
	}

	else
	{
		return sf::Vector2f(posX, posY);
	}

}

sf::Vector2f AGameObject::getScale()
{
	if (this->sprite != NULL)
	{
		return this->sprite->getScale();
	}

	else
	{
		return sf::Vector2f(scaleX, scaleY);
	}
}

sf::FloatRect AGameObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

