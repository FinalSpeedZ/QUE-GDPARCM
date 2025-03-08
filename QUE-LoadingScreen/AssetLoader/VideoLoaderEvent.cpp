#include "VideoLoaderEvent.h"

#include "../AssetLoader/VideoDisplay.h"

#include "../GameObject/GameObjectManager.h"

void VideoLoaderEvent::onFinishedExecution()
{
	VideoDisplay* textureDisplay = new VideoDisplay();
	GameObjectManager::getInstance()->addObject(textureDisplay);
}
