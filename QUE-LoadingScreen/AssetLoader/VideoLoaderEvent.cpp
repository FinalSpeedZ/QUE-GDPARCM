#include "VideoLoaderEvent.h"

#include "../AssetLoader/VideoDisplay.h"

#include "../GameObject/BGObject.h"
#include "../GameObject/GameObjectManager.h"
#include "../GameObject/FPSCounter/FPSCounter.h"

void VideoLoaderEvent::onFinishedExecution()
{
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

    std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->getAllObjects();

    auto it = std::find_if(objectList.begin(), objectList.end(), [](AGameObject* obj) {
        return obj->getName() == "FPSCounter";
        });

    if (it != objectList.end())
    {
        FPSCounter* FPS = new FPSCounter(*(static_cast<FPSCounter*>(*it))); 

        GameObjectManager::getInstance()->deleteObject(*it); 

        GameObjectManager::getInstance()->addObject(FPS); 
    }

	VideoDisplay* textureDisplay = new VideoDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);
}
