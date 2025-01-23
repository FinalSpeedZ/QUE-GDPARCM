#include "MyThread.h"

MyThread::MyThread(int id) 
	: id(id)
{
}

void MyThread::run()
{
	this->running = true;

	while (this->running) 
	{
		std::cout << "Hello from Thread: " << this->id << std::endl;
		this->sleep(1000);
	}
}

void MyThread::dismiss() 
{
	this->running = false;
}