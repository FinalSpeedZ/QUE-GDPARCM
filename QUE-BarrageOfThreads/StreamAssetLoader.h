#pragma once

#include "IETThread.h"
#include "IWorkerAction.h"

class IExecutionEvent;

class StreamAssetLoader : public IWorkerAction
{
public:
	StreamAssetLoader(std::string path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void onStartTask() override;

private:
	std::string path;
	IExecutionEvent* execEvent;
};

