#include "VideoLoaderEvent.h"

#include "../AssetLoader/VideoDisplay.h"

#include "../GameObject/BGObject.h"
#include "../GameObject/GameObjectManager.h"
#include "../GameObject/FPSCounter/FPSCounter.h"

void VideoLoaderEvent::onFinishedExecution()
{
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	VideoDisplay* textureDisplay = new VideoDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);
}
