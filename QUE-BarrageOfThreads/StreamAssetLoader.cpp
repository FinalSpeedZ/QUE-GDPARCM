#include "StreamAssetLoader.h"

#include <iostream>
#include <random>

#include "TextureManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

StreamAssetLoader::StreamAssetLoader(std::string path, IExecutionEvent* executionEvent)
{
	this->path = path;
	this->execEvent = executionEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying stream asset loader. " << std::endl;
}

void StreamAssetLoader::onStartTask()
{
	//std::cout << "Running stream asset loader " << std::endl;

	//simulate loading of very large file
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(2000, 5000);

	std::vector<std::string> tokens = StringUtils::split(path, '/');
	std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;


	this->execEvent->onFinishedExecution();

	delete this;
}

//void StreamAssetLoader::run()
//{
//	std::cout << "Running stream asset loader " << std::endl;
//
//	//simulate loading of very large file
//	std::random_device seeder;
//	std::mt19937 engine(seeder());
//	std::uniform_int_distribution<int> dist(2000, 5000);
//
//	std::vector<std::string> tokens = StringUtils::split(path, '/');
//	std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
//
//	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);
//
//	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
//
//
//	this->execEvent->onFinishedExecution();
//
//	delete this;
//}
