#include "VideoLoader.h"

#include "../Texture/TextureManager.h"
#include "../Thread/IExecutionEvent.h"

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
