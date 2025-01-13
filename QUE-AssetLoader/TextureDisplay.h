#pragma once
#include "AGameObject.h"

class IconObject;

class TextureDisplay : public AGameObject
{
public:
	TextureDisplay();
	~TextureDisplay() = default;

public:
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	void spawnObject();

private:
	std::vector<IconObject*> iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 2000.0f;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0;
	int rowGrid = 0;

	const int MAX_COLUMN = 25;
	const int MAX_ROW = 22;
};


