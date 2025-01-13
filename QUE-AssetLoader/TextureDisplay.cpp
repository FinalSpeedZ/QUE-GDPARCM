#include "TextureDisplay.h"

#include <iostream>

#include "IconObject.h"
#include "Constants.h"
#include "GameObjectManager.h"
#include "TextureManager.h"

TextureDisplay::TextureDisplay()
	: AGameObject("TextureDisplay")
{
}

void TextureDisplay::initialize()
{
	this->iconList.clear();
	this->ticks = 0.0f;
	this->startedStreaming = false;
}

void TextureDisplay::processInput(sf::Event event)
{
}

void TextureDisplay::update(sf::Time deltaTime)
{
	this->ticks += TIME_PER_FRAME.asMilliseconds();

	//std::cout << std::to_string(this->ticks) << std::endl;

    if (this->streamingType == SINGLE_STREAM)
    {
        if (!this->startedStreaming && this->ticks >= this->STREAMING_LOAD_DELAY)
        {
            this->spawnObject();
            this->ticks = 0.0f; 
        }
    }
}

void TextureDisplay::spawnObject()
{
	std::string objectName = "Icon_" + std::to_string(this->iconList.size());

	IconObject* iconObj = new IconObject(objectName, this->iconList.size());

	TextureManager::getInstance()->loadSingleStreamAsset(this->iconList.size());

	this->iconList.push_back(iconObj);

	int IMG_WIDTH = 70;
	int IMG_HEIGHT = 70;

	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;

	iconObj->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	GameObjectManager::getInstance()->addObject(iconObj);
}
