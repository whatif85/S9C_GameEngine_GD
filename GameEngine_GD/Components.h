#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "ECS.h"


struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;

	Transform(float newX, float newY)
	{
		this->xPos = newX;
		this->yPos = newY;

		this->rotation = 0.0f;
	}
};
ECS_DEFINE_TYPE(Transform);


struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite sprite;
	std::string texture;
	unsigned int width, height;

	Sprite2D(std::string filePath)
	{
		texture = filePath;
	}
};
ECS_DEFINE_TYPE(Sprite2D);