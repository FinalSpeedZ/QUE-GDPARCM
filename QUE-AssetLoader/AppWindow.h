#pragma once

#include <SFML/Graphics.hpp>

#include "Constants.h"

class AppWindow
{
private:
	AppWindow();
	~AppWindow() = default;

	AppWindow(const AppWindow&) = delete;
	AppWindow(AppWindow&&) = delete;
	AppWindow& operator=(const AppWindow&) = delete;
	AppWindow& operator=(AppWindow&&) = delete;

public:
	static void initialize();
	static AppWindow* getInstance();

private:
	static AppWindow* sharedInstance;


public:
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void draw();

private:
	sf::RenderWindow window;
};

