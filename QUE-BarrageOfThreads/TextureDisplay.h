#pragma once

#include "AGameObject.h"
#include "IExecutionEvent.h"
#include <mutex>

class IconObject;

class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();

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
	const float STREAMING_LOAD_DELAY = 0.01f; //greatly reduce streaming load delay to demonstrate performance drop.
	const StreamingType streamingType = SINGLE_STREAM;

	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0;
	int rowGrid = 0;

	int numDisplayed = 0;

	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	std::mutex guard; //used to avoid possible race conditions when spawning objects. Not really required for this exercise. Will be explained in future lessons.
};

