#pragma once

#include <unordered_map>

#include "SFML/Graphics.hpp"

class IExecutionEvent;

class TextureManager
{
public:
	static TextureManager* getInstance();

public:
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadStreamingAssets(); //loading of assets during runtime
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory

	sf::Texture* getFromTextureMap(const std::string assetName, int frameIndex);
	int getNumFrames(const std::string assetName);

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

	const std::string STREAMING_PATH = "../Media/Streaming/";
	int streamingAssetCount = 0;

};