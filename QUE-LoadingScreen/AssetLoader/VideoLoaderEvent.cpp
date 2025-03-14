#include "VideoLoaderEvent.h"

#include "../AssetLoader/VideoDisplay.h"

#include "../GameObject/BGObject.h"
#include "../GameObject/GameObjectManager.h"
#include "../Thread/IETThread.h"

void VideoLoaderEvent::onFinishedExecution()
{
	GameObjectManager::getInstance()->deleteObjectByName("Pipes");
	GameObjectManager::getInstance()->deleteObjectByName("Player");
	GameObjectManager::getInstance()->deleteObjectByName("FlappyBG");

	BGObject* bgObject = new BGObject("VideoBG");
	GameObjectManager::getInstance()->addObject(bgObject);

	VideoDisplay* textureDisplay = new VideoDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);
}
