#pragma once
#include "IETThread.h"

class MyThread : public IETThread
{
public:
	MyThread() = default;
	explicit MyThread(int id);

public:
	void run() override;
	void dismiss();

private:
	int id;
	bool running = false;
};

