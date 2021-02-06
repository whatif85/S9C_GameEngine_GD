#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem() {}

PhysicsSystem::~PhysicsSystem() {}


bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<struct BoxCollider> touchingEntity,
	ECS::ComponentHandle<struct BoxCollider> touchedEntity,
	float x, float y)
{
	return touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
		touchedEntity->bottomEdge > touchingEntity->topEdge + y;

	/*
	// Check X for collision
	if (touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x)
	{
		// Check Y for collision
		if (touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
			touchedEntity->bottomEdge > touchingEntity->topEdge + y)
		{
			return true;
		}
	}

	return false;
	*/
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<struct BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle,
	float x, float y)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = _touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = _touchedRectTop + touchedRectangle.getGlobalBounds().height;

	return touchingEntity->rightEdge + x > _touchedRectLeft &&
		_touchedRectRight > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > _touchedRectTop &&
		_touchedRectBottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<struct BoxCollider> touchingBox,
	ECS::ComponentHandle<struct BoxCollider> touchedBox)
{
	return touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge;
}


void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<struct Transform> transform,
	ECS::ComponentHandle<struct BoxCollider> touchingEntity,
	ECS::ComponentHandle<struct BoxCollider> touchedEntity)
{
	// Scenario dealing with collision from the right side by accelerating rightward
	if (transform->xSpeed > 0 &&
		touchingEntity->rightEdge + transform->xSpeed > touchedEntity->leftEdge &&
		touchingEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward
	if (transform->ySpeed > 0 &&
		touchingEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
		touchingEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (transform->xSpeed < 0 &&
		touchingEntity->leftEdge + transform->xSpeed < touchedEntity->rightEdge &&
		touchingEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward
	if (transform->ySpeed < 0 &&
		touchingEntity->topEdge + transform->ySpeed < touchedEntity->bottomEdge &&
		touchingEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<struct Transform> transform,
	ECS::ComponentHandle<struct BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = _touchedRectLeft + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = _touchedRectTop + touchedRectangle.getGlobalBounds().height;

	// Scenario dealing with collision from the right side by accelerating rightward
	if (transform->xSpeed > 0 &&
		touchingEntity->rightEdge + transform->xSpeed > _touchedRectLeft &&
		touchingEntity->topEdge < _touchedRectBottom &&
		touchingEntity->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward
	if (transform->ySpeed > 0 &&
		touchingEntity->bottomEdge + transform->ySpeed > _touchedRectTop &&
		touchingEntity->leftEdge < _touchedRectRight &&
		touchingEntity->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (transform->xSpeed < 0 &&
		touchingEntity->leftEdge + transform->xSpeed < _touchedRectRight &&
		touchingEntity->topEdge < _touchedRectBottom &&
		touchingEntity->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward
	if (transform->ySpeed < 0 &&
		touchingEntity->topEdge + transform->ySpeed < _touchedRectBottom &&
		touchingEntity->leftEdge < _touchedRectRight &&
		touchingEntity->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}
}

/*
void PhysicsSystem::PushEntity(
	ECS::Entity* touchingEntity,
	ECS::Entity* touchedEntity)
{
	ECS::ComponentHandle<Transform> _touchingTransform = touchingEntity->get<Transform>();
	ECS::ComponentHandle<Transform> _touchedTransform = touchedEntity->get<Transform>();

	if ((_touchingTransform->xPos - _touchingTransform->_newXSpeed) < (_touchedTransform->xPos - _touchingTransform->_newXSpeed))
	{
		_touchedTransform->xPos++;
	}
	else if ((_touchingTransform->xPos - _touchingTransform->_newXSpeed) > (_touchedTransform->xPos - _touchingTransform->_newXSpeed))
	{
		_touchedTransform->xPos--;
	}
	else if ((_touchingTransform->yPos - _touchingTransform->_newYSpeed) < (_touchedTransform->yPos - _touchingTransform->_newYSpeed))
	{
		_touchedTransform->yPos++;
	}
	else if ((_touchingTransform->yPos - _touchingTransform->_newYSpeed) > (_touchedTransform->yPos - _touchingTransform->_newYSpeed))
	{
		_touchedTransform->yPos--;
	}
}
*/

void PhysicsSystem::PushEntity(
	ECS::Entity* touchingEntity,
	ECS::Entity* touchedEntity)
{
	float _newTouchingX = touchingEntity->get<struct Transform>()->xPos;
	float _newTouchingY = touchingEntity->get<struct Transform>()->yPos;

	float _newTouchedX = touchedEntity->get<struct Transform>()->xPos;
	float _newTouchedY = touchedEntity->get<struct Transform>()->yPos;

	float _newXSpeed = touchingEntity->get<struct Transform>()->xSpeed;
	float _newYSpeed = touchingEntity->get<struct Transform>()->ySpeed;

	if (_newXSpeed > 0 && _newTouchingX <= _newTouchedX)
	{
		touchedEntity->get<struct Transform>()->xPos = touchingEntity->get<struct BoxCollider>()->rightEdge;
	}
	else if (_newXSpeed < 0 && _newTouchingX >= _newTouchedX)
	{
		touchedEntity->get<struct Transform>()->xPos = touchingEntity->get<struct BoxCollider>()->leftEdge - touchedEntity->get<struct BoxCollider > ()->boxWidth;
	}

	if (_newYSpeed > 0 && _newTouchingY <= _newTouchedY)
	{
		touchedEntity->get<struct Transform>()->yPos = touchingEntity->get<struct BoxCollider>()->bottomEdge;
	}
	else if (_newYSpeed < 0 && _newTouchingY >= _newTouchedY)
	{
		touchedEntity->get<struct Transform>()->yPos = touchingEntity->get<struct BoxCollider>()->topEdge - touchedEntity->get<struct BoxCollider >()->boxHeight;
	}



}


void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<struct BoxCollider, struct Sprite2D, struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct BoxCollider> box,
			ECS::ComponentHandle<struct Sprite2D> sprite,
			ECS::ComponentHandle<struct Transform> transform
			) -> void
	{
		box->Update(transform->xPos, transform->yPos,
			sprite->sprite.getTextureRect().width,
			sprite->sprite.getTextureRect().height);
	});

	world->each<struct BoxCollider, struct Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<struct BoxCollider> touchingBox,
			ECS::ComponentHandle<struct Transform> transform1
			) -> void
	{
		world->each<struct BoxCollider, struct Transform>(
			[&](ECS::Entity* touchedEntity,
				ECS::ComponentHandle<struct BoxCollider> touchedBox,
				ECS::ComponentHandle<struct Transform> transform2
				) -> void
		{
			// statement to avoid comparing same entity to itself
			if (touchingEntity->getEntityId() != touchedEntity->getEntityId())
			{
				// initial collision check
				if (IsColliding(touchingBox, touchedBox) == true)
				{
					// final collision check
					PushEntity(touchingEntity, touchedEntity);
				}
			}
		});
	});

	world->each<struct Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct Transform> transform
			) -> void
	{
		transform->Move();
	});

	// TODO: Circle collision?
}
