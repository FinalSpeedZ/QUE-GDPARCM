#pragma once
#include <mutex>

#include "IWorkerAction.h"

class Camera;
class Hittable;
class ImageSaver;
class IExecutionEvent;

class WorkerRaytracer : public IWorkerAction
{
public:
	WorkerRaytracer(int imgWidth, int imgHeight, int startRow, int endRow,
		Camera* camera, Hittable* world, ImageSaver* imageSaver, IExecutionEvent* executionEvent);
	~WorkerRaytracer() = default;

public:
	// Thread Function
	void onStartTask() override;

private:
	std::mutex guard;

	int imgWidth;
	int imgHeight;

	int startRow;
	int endRow;

	int samplesPerPixel;
	int maxDepth;

	Camera* camera;
	Hittable* world;
	ImageSaver* imageSaver;

	IExecutionEvent* executionEvent;
};

