#pragma once
#include "../Thread/IExecutionEvent.h"

class VideoLoaderEvent : public IExecutionEvent
{
public:
	VideoLoaderEvent() = default;
	~VideoLoaderEvent() = default;

	void onFinishedExecution() override;
};

