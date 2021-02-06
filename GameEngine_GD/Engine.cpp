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

	mainCamera = MainCamera(sf::Vector2f(
		this->window->getSize().x / 2,
		this->window->getSize().y / 2));

	while (this->window->isOpen() == true)
	{
		Update();
	}
}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
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

			exit(EXIT_SUCCESS);
		}
	}

	world->tick(10.0f);

	mainCamera.Update(world, 10.0f, window);
}
