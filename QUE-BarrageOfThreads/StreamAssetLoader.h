#pragma once

#include "IETThread.h"

class IExecutionEvent;

class StreamAssetLoader : public IETThread
{
public:
	StreamAssetLoader(std::string path, IExecutionEvent* executionEvent);
	~StreamAssetLoader();

private:
	void run() override;

private:
	std::string path;
	IExecutionEvent* execEvent;
};

