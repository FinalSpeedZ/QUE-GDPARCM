#include "TextureManager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include "../Utils/StringUtils.h"
#include "../Thread/IETThread.h"
#include "../Thread/StreamAssetLoader.h"
#include "../Thread/IExecutionEvent.h"

#include "../AssetLoader/VideoLoader.h"
#include "../AssetLoader/VideoLoaderEvent.h"

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->threadPool = new ThreadPool("TextureManagerPool", std::thread::hardware_concurrency());
	this->threadPool->startScheduler();

	this->streamTextureList.reserve(3000);
	this->textureMap.reserve(3000);

	IExecutionEvent* event = new VideoLoaderEvent(); 
	VideoLoader* videoLoader = new VideoLoader(FRAMES_PATH, event);
	this->threadPool->scheduleTask(videoLoader);

}

void TextureManager::loadVideoAssetsInBackground()
{
	int index = 0; 
	for (const auto& entry : std::filesystem::directory_iterator(FRAMES_PATH))
	{
		if (entry.path().extension() == ".png")
		{
			std::string path = entry.path().string();
			std::vector<std::string> tokens = StringUtils::split(path, '/');
			std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

			this->instantiateAsTexture(path, std::to_string(index), false);
			std::cout << "[TextureManager] Loaded texture: " << assetName << " at index " << index << std::endl;
			index++;
		}
	}

	std::string backgroundPath = "../Media/Background.jpg";
	if (std::filesystem::exists(backgroundPath))
	{
		this->instantiateAsTexture(backgroundPath, "BackgroundBG", false);
		std::cout << "[TextureManager] Loaded background texture: " << backgroundPath << std::endl;
	}

}

void TextureManager::loadStreamingAssets()
{
	for (const auto& entry : std::filesystem::directory_iterator(FRAMES_PATH))
	{
		IETThread::sleep(200);

		std::string path = entry.path().generic_string();
		std::vector<std::string> tokens = StringUtils::split(path, '/');
		std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, true);

		std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	}
}

void TextureManager::loadSingleStreamAsset(int index, IExecutionEvent* executionEvent)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(FRAMES_PATH))
	{
		if (index == fileNum)
		{
			std::string path = entry.path().generic_string();
			StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			//this->threadPool->scheduleTask(assetLoader);

			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::getFromTextureMap(const std::string assetName, int frameIndex)
{
	if (!this->textureMap[assetName].empty())
	{
		return this->textureMap[assetName][frameIndex];
	}

	else
	{
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return NULL;
	}
}

int TextureManager::getNumFrames(const std::string assetName)
{
	if (!this->textureMap[assetName].empty())
	{
		return this->textureMap[assetName].size();
	}

	else
	{
		std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
		return 0;
	}
}

sf::Texture* TextureManager::getBaseTextureFromList(const int index)
{
	return this->baseTextureList[index];
}

int TextureManager::getNumLoadedBaseTextures() const
{
	return this->streamTextureList.size();
}

sf::Texture* TextureManager::getStreamTextureFromList(const int index)
{
	return this->streamTextureList[index];
}

int TextureManager::getNumLoadedStreamTextures() const
{
	return this->streamTextureList.size();
}

void TextureManager::countStreamingAssets()
{
	this->streamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(FRAMES_PATH))
	{
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(std::string path, std::string assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(path))
	{
		std::cerr << "[TextureManager] ERROR: Failed to load texture: " << path << std::endl;
		delete texture;
		return;
	}
	texture->setSmooth(false);


	this->textureMap[assetName].push_back(texture);

	if (isStreaming)
	{
		this->streamTextureList.push_back(texture);
	}
	else
	{
		this->baseTextureList.push_back(texture);
	}

} 