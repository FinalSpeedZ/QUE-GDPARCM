#include "VideoDisplay.h"

#include "../Texture/TextureManager.h"
#include "../Window/AppWindow.h"
#include "../GameObject/GameObjectManager.h"
#include "../GameObject/IconObject.h"

#include "../Settings.h"

#include <iostream>

VideoDisplay::VideoDisplay() : AGameObject("VideoDisplay")
{
    this->iconList.clear();

    if (!bgm.openFromFile("../Media/spaceCats.mp3"))
    {
        std::cerr << "Failed to load background music!" << std::endl;
    }
    else
    {
        bgm.setVolume(100); 
        bgm.play();        
    }
}

void VideoDisplay::initialize()
{
}

void VideoDisplay::processInput(sf::Event event)
{
}

void VideoDisplay::update(sf::Time deltaTime)
{
    this->ticks += deltaTime.asMilliseconds();

    if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY && this->numDisplayed < NUM_FRAMES)
    {
        this->ticks = 0.0f;
        this->spawnObject();

        if (this->numDisplayed == 0)
        {
            bgm.play();
        }

        this->numDisplayed++;
    }
}

void VideoDisplay::spawnObject()
{
    if (this->iconList.size() >= 2)
    {
        AGameObject* oldestIcon = this->iconList.front();
        this->iconList.erase(this->iconList.begin());
        GameObjectManager::getInstance()->deleteObject(oldestIcon);
    }

    std::string objectName = "Icon_" + std::to_string(numDisplayed);
    IconObject* iconObj = new IconObject(objectName, numDisplayed);
    this->iconList.push_back(iconObj);

    int IMG_WIDTH = 1280;
    int IMG_HEIGHT = 720;

    sf::Vector2u windowSize = sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);

    float x = (windowSize.x - IMG_WIDTH) * 0.5f;
    float y = (windowSize.y - IMG_HEIGHT) * 0.5f;

    iconObj->setPosition(x, y);

    GameObjectManager::getInstance()->addObject(iconObj);
}

void VideoDisplay::onFinishedExecution()
{

}
