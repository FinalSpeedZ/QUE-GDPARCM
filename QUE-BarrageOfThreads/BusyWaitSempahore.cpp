#include "BusyWaitSempahore.h"

#include "IETThread.h"

BusyWaitSempahore::BusyWaitSempahore(int available, int limit)
{
	this->permits = available;
	this->maxPermits = limit;
	this->guard = new Mutex();
}

BusyWaitSempahore::BusyWaitSempahore(int limit)
{
	this->maxPermits = limit;
	this->permits = this->maxPermits;
	this->guard = new Mutex();
}

void BusyWaitSempahore::acquire()
{
	this->guard->lock();
	if (this->permits > 0)
	{
		this->permits = this->permits - 1;
		this->guard->unlock();
	}
	else
	{
		this->guard->unlock();
		this->wait();

		this->guard->lock();
		this->permits = this->permits - 1;
		this->guard->unlock();

	}
}

void BusyWaitSempahore::release()
{
	this->guard->lock();
	if (this->permits < this->maxPermits)
	{
		this->permits = this->permits + 1;
	}
	this->guard->unlock();
}

void BusyWaitSempahore::wait() const
{
	while (this->permits == 0)
	{
		IETThread::sleep(1);
	}
}
