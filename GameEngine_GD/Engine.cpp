#include "Engine.h"


Engine::Engine(void) {}

Engine::~Engine(void) {}

Engine& Engine::GetInstance(void)
{
	static Engine _instance;

	return _instance;
}

void Engine::Start(sf::RenderWindow* win)
{
	bQuit = false;
	this->window = win;

	while (this->window->isOpen() == true)
	{
		Update();
	}
}

void Engine::Update()
{
	sf::Event _event;

	// listen to any event occurring while the program
	while (window->pollEvent(_event) == true)
	{
		// close requested event
		if (_event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}
