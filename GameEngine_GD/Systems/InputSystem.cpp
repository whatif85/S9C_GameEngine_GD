#include "InputSystem.h"


InputSystem::InputSystem(sf::RenderWindow* win)
	: window(win) {}

InputSystem::~InputSystem() {}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	GetKeyEvents(world);
}

void InputSystem::GetKeyEvents(ECS::World* world)
{
	world->each<struct InputController>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input) -> void
	{
		input->wKey = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		input->sKey = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		input->aKey = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		input->dKey = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		input->aKey = sf::
	});
}
