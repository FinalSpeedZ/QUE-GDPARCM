#include "VideoLoader.h"

#include "../GameObject/BGObject.h"
#include "../Texture/TextureManager.h"
#include "../Thread/IExecutionEvent.h"

#include "../GameObject/GameObjectManager.h"
#include "../GameObject/Player/Player.h"

VideoLoader::VideoLoader(int index, IExecutionEvent* executionEvent)
{
	this->execEvent = executionEvent;
    this->index = index;
}

VideoLoader::~VideoLoader()
{
	std::cout << "Destroying video loader. " << std::endl;
}

void VideoLoader::onStartTask()
{
    TextureManager::getInstance()->loadVideoAssetsInBackground(index);

    //this->execEvent->onFinishedExecution();

    delete this;
}
