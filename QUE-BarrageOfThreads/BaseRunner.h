#include <SFML/Graphics.hpp>
#include <vector>

class BaseRunner : private sf::NonCopyable
{
public:
	BaseRunner();

public:
	void run();

public:
	static BaseRunner* getInstance();
	float getFPS() const;

private:
	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

public:
	static const sf::Time TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

private:
	static BaseRunner* sharedInstance;

	sf::RenderWindow window;
	float fps = 0.0f;
};


