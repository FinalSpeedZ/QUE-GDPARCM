#include "VideoLoader.h"

#include "../GameObject/BGObject.h"
#include "../Texture/TextureManager.h"
#include "../Thread/IExecutionEvent.h"

#include "../GameObject/GameObjectManager.h"
#include "../GameObject/Player/Player.h"

VideoLoader::VideoLoader(std::string path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;
}

VideoLoader::~VideoLoader()
{
	std::cout << "Destroying video loader. " << std::endl;
}

void VideoLoader::onStartTask()
{
    TextureManager::getInstance()->loadVideoAssetsInBackground();

    this->execEvent->onFinishedExecution();

    delete this;
}
