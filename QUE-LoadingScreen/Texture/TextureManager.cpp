#include "TextureManager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include "../Settings.h"
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

	this->loadLoadingScreenAssets();

	const int totalFrames = 2057;  // You have exactly 2057 frames
	const int numThreads = 4;
	const int baseChunkSize = totalFrames / numThreads;
	const int remainder = totalFrames % numThreads;

	int startIndex = 0;

	for (int i = 0; i < numThreads; i++)
	{
		int chunkSize = baseChunkSize + (i < remainder ? 1 : 0); // Distribute remainder evenly
		IExecutionEvent* event = new VideoLoaderEvent();
		VideoLoader* videoLoader = new VideoLoader(startIndex, event);
		this->threadPool->scheduleTask(videoLoader);

		startIndex += chunkSize;
	}
}

void TextureManager::loadVideoAssetsInBackground(int startIndex)
{
	std::vector<std::filesystem::path> pngFiles;

	for (const auto& entry : std::filesystem::directory_iterator(FRAMES_PATH))
	{
		if (entry.path().extension() == ".png")
		{
			pngFiles.push_back(entry.path());
		}
	}

	std::sort(pngFiles.begin(), pngFiles.end());

	if (startIndex >= static_cast<int>(pngFiles.size())) return;

	int endIndex = std::min(startIndex + 515, static_cast<int>(pngFiles.size())); 

	for (int i = startIndex; i < endIndex; i++)
	{
		IETThread::sleep(100);

		std::string path = pngFiles[i].string();
		std::string assetName = "Icon_" + std::to_string(i);

		this->instantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}


void TextureManager::loadLoadingScreenAssets()
{
	std::string backgroundPath = "../Media/VideoBG.jpg";
	if (std::filesystem::exists(backgroundPath))
	{
		this->instantiateAsTexture(backgroundPath, "VideoBG", false);
		std::cout << "[TextureManager] Loaded background texture: " << backgroundPath << std::endl;
	}

	std::string playerPath = "../Media/CatAhh.png";
	if (std::filesystem::exists(playerPath))
	{
		this->instantiateAsTexture(playerPath, "CatAhh", false);
		std::cout << "[TextureManager] Loaded background texture: " << playerPath << std::endl;
	}

	playerPath = "../Media/CatOhm.png";
	if (std::filesystem::exists(playerPath))
	{
		this->instantiateAsTexture(playerPath, "CatOhm", false);
		std::cout << "[TextureManager] Loaded background texture: " << playerPath << std::endl;
	}

	std::string loadingPath = "../Media/LoadingPaw.png";
	if (std::filesystem::exists(loadingPath))
	{
		this->instantiateAsTexture(loadingPath, "LoadingPaw", false);
		std::cout << "[TextureManager] Loaded background texture: " << loadingPath << std::endl;
	}

	std::string pipePath = "../Media/pipe.png";
	if (std::filesystem::exists(pipePath))
	{
		this->instantiateAsTexture(pipePath, "Pipe", false);
		std::cout << "[TextureManager] Loaded background texture: " << playerPath << std::endl;
	}

	 backgroundPath = "../Media/flappyBG.png";
	if (std::filesystem::exists(backgroundPath))
	{
		this->instantiateAsTexture(backgroundPath, "FlappyBG", false);
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
	return this->baseTextureList.size();
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