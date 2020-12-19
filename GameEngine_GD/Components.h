#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "ECS.h"


struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos, rotation;
	float xSpeed, ySpeed;

	Transform(float newX, float newY)
		: xPos(newX), yPos(newY)
	{
		this->xSpeed = 0;
		this->ySpeed = 0;

		this->rotation = 0.0f;
	}

	void UpdateSpeed(float x, float y)
	{
		this->xSpeed = x;
		this->ySpeed = y;
	}

	void Move()
	{
		// halve speed when moving diagonally
		if (xSpeed != 0 && ySpeed != 0)
		{
			xSpeed /= 2;
			ySpeed /= 2;
		}

		xPos += xSpeed;
		yPos += ySpeed;
	}

	void Stop()
	{
		xSpeed = 0;
		ySpeed = 0;
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


struct Animator
{
public:
	ECS_DECLARE_TYPE;

	int frameWidth, frameHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;

	float currentTime, nextTimeFrame;

	bool bIsFacingRight;

	Animator(
		int newWidth, int newHeight,
		float timeBetweenFrames,
		int newColumns, int newRows)
	{
		this->frameWidth = newWidth;
		this->frameHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		this->nextTimeFrame = timeBetweenFrames;
		this->totalColumns = newColumns;
		this->totalRows = newRows;

		currentTime = 0;

		bIsFacingRight = true;
	}
};
ECS_DEFINE_TYPE(Animator);


struct InputController
{
public:
	ECS_DECLARE_TYPE;

	bool bInputActive;

	// Key states
	bool wKey, aKey, sKey, dKey;

	InputController()
	{
		bInputActive = true;

		wKey = false;
		aKey = false;
		sKey = false;
		dKey = false;
	}
};
ECS_DEFINE_TYPE(InputController);


struct BoxCollider
{
public:
	ECS_DECLARE_TYPE;

	float leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider()
	{
		this->leftEdge = 0;
		this->rightEdge = 0;
		this->topEdge = 0;
		this->bottomEdge = 0;
	}

	void Update(float xSide, float ySide, float width, float height)
	{
		this->leftEdge = xSide;
		this->rightEdge = xSide + width;
		this->topEdge = ySide;
		this->bottomEdge = ySide + height;
	}
};
ECS_DEFINE_TYPE(BoxCollider);