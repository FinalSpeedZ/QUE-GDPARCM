#pragma once

#include "../Thread/IETThread.h"
#include "../Thread/IWorkerAction.h"

class IExecutionEvent;

class VideoLoader : public IWorkerAction
{
public:
	VideoLoader(int index, IExecutionEvent* executionEvent);
	~VideoLoader();

private:
	void onStartTask() override;

private:
	int index;
	IExecutionEvent* execEvent;
};



