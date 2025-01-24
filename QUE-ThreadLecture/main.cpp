// QUE-ThreadLecture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <thread>
#include "MyThread.h"

void testFunc(int x)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << "Hello World! from Thread #" << x << std::endl;
}

int main()
{
    std::cout << "Hello World! from Thread main\n";

	constexpr int N = 100;

	MyThread tl[N];

	for (int i = 0; i < N; i++)
	{
		tl[i] = MyThread(i);
		tl[i].start();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	for (int i = 0; i < N; i++)
	{
		tl[i].dismiss();
	}

	//std::this_thread::sleep_for(std::chrono::milliseconds(400));

	/* NOTES */
	// telling thread to report results back to main thread
	// thread.join(): waits for completion of other threads to finish
		// join are not ideal for persistent threads and advanced sync mechanisms
	// thread.detach(): separates the thread to execute asynchronous from main thread
		// more control as it allows persistent background threads
	// if all threads finish at the same clock cycle they would overlap

	std::cout << "Bye World! from Thread main" << std::endl;	
}