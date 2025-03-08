#pragma once

#include "../Thread/IETThread.h"
#include "../Thread/IWorkerAction.h"

class IExecutionEvent;

class VideoLoader : public IWorkerAction
{
public:
	VideoLoader(std::string path, IExecutionEvent* executionEvent);
	~VideoLoader();

private:
	void onStartTask() override;

private:
	std::string path;
	IExecutionEvent* execEvent;
};



