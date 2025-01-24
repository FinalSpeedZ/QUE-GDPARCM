#include "TextureManager.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include "IETThread.h"
#include "StringUtils.h"

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager::TextureManager()
{
	this->countStreamingAssets();
}

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
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

void TextureManager::loadSingleStreamAsset(int index)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) 
	{
		if (index == fileNum)
		{
			//simulate loading of very large file
			//<code here for thread sleeping. Fill this up only when instructor told so.>

			//IETThread::sleep(2000);

			std::string filePath = entry.path().string();
			sf::Texture* texture = new sf::Texture();

			if (texture->loadFromFile(filePath))
			{
				std::string assetName = entry.path().filename().stem().string();

				this->instantiateAsTexture(filePath, assetName, true);

				std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			}
			else
			{
				std::cerr << "[TextureManager] Failed to load texture: " << filePath << std::endl;
				delete texture; 
			}

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


