#include "TextureManager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include "StringUtils.h"
#include "IETThread.h"
#include "StreamAssetLoader.h"
#include "IExecutionEvent.h"

//a singleton class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == NULL) 
	{
		sharedInstance = new TextureManager();
	}
	return sharedInstance;
}

TextureManager::TextureManager()
{
	this->countStreamingAssets();
}

void TextureManager::loadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("../Media/assets.txt");
	std::string path;

	while (std::getline(stream, path))
	{
		std::vector<std::string> tokens = StringUtils::split(path, '/');
		std::string assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::loadStreamingAssets()
{
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
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

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
	{
		if (index == fileNum)
		{
			std::string path = entry.path().generic_string();
			StreamAssetLoader* assetLoader = new StreamAssetLoader(path, executionEvent);
			assetLoader->start();

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
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
	{
		this->streamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << this->streamingAssetCount << std::endl;
}

void TextureManager::instantiateAsTexture(std::string path, std::string assetName, bool isStreaming)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
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
