#pragma once

#include "../GameObject/AGameObject.h"
#include "../Thread/IExecutionEvent.h"

#include <SFML/Audio/Music.hpp>

#include <mutex>

class IconObject;

class VideoDisplay : public AGameObject, public IExecutionEvent
{
public:
	VideoDisplay();

public:
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

private:
	void spawnObject();
	void onFinishedExecution() override;

private:
	std::vector<IconObject*> iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 29.97f;
	const StreamingType streamingType = SINGLE_STREAM;

	float ticks = 0.0f;
	bool startedStreaming = false;

	int numDisplayed = 0;

	sf::Music bgm;

	std::mutex guard; 
};

