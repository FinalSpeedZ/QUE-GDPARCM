#pragma once
#include <mutex>

class BusyWaitSempahore
{
public:
	BusyWaitSempahore(int available, int limit);
	BusyWaitSempahore(int limit);
	~BusyWaitSempahore() = default;

public:
	void acquire();
	void release();

private:
	typedef std::mutex Mutex;
	Mutex* guard;

	int permits = 0;
	int maxPermits = 0;

	void wait() const; // sleeps the thread and awakes when permits are enough
};

