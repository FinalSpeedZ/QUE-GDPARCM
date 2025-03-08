#pragma once

#include <unordered_map>

#include "../Thread/ThreadPool.h"
#include <queue>

#include "SFML/Graphics.hpp"

class IExecutionEvent;

class TextureManager
{
public:
	static void initialize();
	static TextureManager* getInstance();

public:
	void loadVideoAssetsInBackground();
	void loadStreamingAssets(); //loading of assets during runtime
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory

	sf::Texture* getFromTextureMap(const std::string assetName, int frameIndex);
	int getNumFrames(const std::string assetName);

	sf::Texture* getBaseTextureFromList(const int index);
	int getNumLoadedBaseTextures() const;

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;

	void instantiateAsTexture(std::string path, std::string assetName, bool isStreaming);

private:
	void countStreamingAssets();

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private

private:
	static TextureManager* sharedInstance;

	std::unordered_map<std::string, std::vector<sf::Texture*>> textureMap;
	std::vector<sf::Texture*> baseTextureList;
	std::vector<sf::Texture*> streamTextureList;

	std::queue<int> textureDeletionQueue;

	const std::string FRAMES_PATH = "../Media/VideoFrames";
	int streamingAssetCount = 0;

	ThreadPool* threadPool;
};