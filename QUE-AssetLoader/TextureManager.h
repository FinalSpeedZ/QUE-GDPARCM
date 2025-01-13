#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <SFML/Graphics.hpp>

class TextureManager
{
private:
	TextureManager();
	~TextureManager() = default;

	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

public:
	static void initialize();
	static TextureManager* getInstance();

private:
	static TextureManager* sharedInstance;

public:
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const std::string assetName, int frameIndex);
	int getNumFrames(const std::string assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;

private:
	void countStreamingAssets();
	void instantiateAsTexture(std::string path, std::string assetName, bool isStreaming);

private:
	std::unordered_map<std::string, std::vector<sf::Texture*>> textureMap;
	std::vector<sf::Texture*> baseTextureList;
	std::vector<sf::Texture*> streamTextureList;

	const std::string STREAMING_PATH = "../Media/Streaming/";
	int streamingAssetCount = 0;
};

