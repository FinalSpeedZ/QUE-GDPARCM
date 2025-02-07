#pragma once
#include "Camera.h"
#include "IExecutionEvent.h"
#include "ThreadPool.h"


class Hittable;

class Renderer : public IExecutionEvent
{
public:
	Renderer();
	~Renderer() = default;

	void run();

	Hittable* createWorld(int smallSpheres);

public:
	// Thread Function
	void onFinishedExecution() override;

private:
	Camera* camera;
	Hittable* world;

	double aspectRatio = 1.0f / 1.0f;
	int imgWidth = 1080;
	int imgHeight = 1080;
	int samplesPerPixel = 500;
	int rayMaxDepth = 50;

	int threadCount = 1080;
	int linesRemaining = this->imgHeight;
	int rowsPerTask = 1;

	ThreadPool* threadPool;

	ImageSaver* image;
	std::mutex guard;

	bool isRunning = false;
};

