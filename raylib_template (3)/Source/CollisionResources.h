#pragma once
#include "raylib.h"

enum SimulationState
{
	CircleCircleSim,
	CircleBoundingBoxSim,
	BoundingBoxBoundingBoxSim,
	CircleLineSegmentSim
};

struct CollisionDetection
{
	bool CircleCircle(Vector2 circle1Pos, float circle1Radius, Vector2 circle2Pos, float circle2Radius);
	bool CircleBoundingBox(Vector2 circlePos, float circleRadius, Vector2 boxPos, Vector2 boxSize);
	bool BoundingBoxBoundingBox(Vector2 box1Pos, Vector2 box1Size, Vector2 box2Pos, Vector2 box2Size);
	bool CircleLineSegment(Vector2 circle1Pos, float circle1Radius, Vector2 LinePos1, Vector2 LinePos2);
};

struct CollisionSimulationButtons 
{
	Texture2D buttonTexture;
	Font font;

	Vector2 circleCircleButtonPos;
	Vector2 circleBoundingBoxButtonPos;
	Vector2 boundingBoxBoundingBoxButtonPos;
	Vector2 circleLineSegmentButtonPos;

	const float buttonWidth = 260.0f;
	const float buttonHeight = 65.0f;
	const float buttonSpacing = 10.0f;

	CollisionSimulationButtons(Texture2D _buttonTexture, Font _font)
	{
		buttonTexture = _buttonTexture;
		font = _font;

		circleCircleButtonPos = Vector2(((float)GetScreenWidth() / 2.0f) - ((buttonWidth * 2.0f) + (buttonSpacing * 1.5f)), (float)GetScreenHeight() - 130.0f);
		circleBoundingBoxButtonPos = Vector2(((float)GetScreenWidth() / 2.0f) - (buttonWidth + (buttonSpacing / 2.0f)), (float)GetScreenHeight() - 130.0f);
		boundingBoxBoundingBoxButtonPos = Vector2(((float)GetScreenWidth() / 2.0f) + (buttonSpacing / 2.0f), (float)GetScreenHeight() - 130.0f);
		circleLineSegmentButtonPos = Vector2(((float)GetScreenWidth() / 2.0f) + (buttonWidth + (buttonSpacing * 1.5f)), (float)GetScreenHeight() - 130.0f);
	}

	void Update(CollisionDetection collisionDetection, SimulationState* state);
	void Render(CollisionDetection collisionDetection);
};

struct CircleCircleCollisionSimulation
{
	Vector2 circle1Pos;
	Vector2 circle2Pos;
	const float circle1Radius = 120.0f;;
	const float circle2Radius = 120.0f;
	bool holdingCircle1;
	bool holdingCircle2;

	Font font;
	Vector2 oldMousePos;

	CircleCircleCollisionSimulation(Font _font)
	{
		font = _font;
		circle1Pos = Vector2((float)GetScreenWidth() - 300.0f, ((float)GetScreenHeight() / 2.0f) - 50.0f);
		circle2Pos = Vector2(300.0f, ((float)GetScreenHeight() / 2.0f) - 50.0f);
		holdingCircle1 = false;
		holdingCircle2 = false;
		oldMousePos = Vector2();
	}

	void Update(CollisionDetection collisionDetection);
	void Render(CollisionDetection collisionDetection);
};

struct CircleBoundingBoxCollisionSimulation
{
	Font font;
	Vector2 oldMousePos;

	Vector2 circlePos;
	Vector2 boxPos;
	const float circleRadius = 100.0f;
	const Vector2 boxSize = Vector2(250.0f, 150.0f);
	bool holdingCircle;
	bool holdingBox;

	CircleBoundingBoxCollisionSimulation(Font _font)
	{
		font = _font;
		circlePos = Vector2((float)GetScreenWidth() - 300.0f, ((float)GetScreenHeight() / 2.0f) - 50.0f);
		holdingCircle = false;
		boxPos = Vector2(175.0f, ((float)GetScreenHeight() / 2.0f) - 125.0f);
		holdingBox = false;
		oldMousePos = Vector2();
	}

	void Update(CollisionDetection collisionDetection);
	void Render(CollisionDetection collisionDetection);
};

struct BoundingBoxBoundingBoxCollisionSimulation
{
	Font font;
	Vector2 oldMousePos;

	Vector2 box1Pos;
	Vector2 box2Pos;
	const Vector2 box1Size = Vector2(200.0f, 250.0f);
	const Vector2 box2Size = Vector2(250.0f, 150.0f);
	bool holdingBox1;
	bool holdingBox2;

	BoundingBoxBoundingBoxCollisionSimulation(Font _font)
	{
		font = _font;
		box1Pos = Vector2((float)GetScreenWidth() - 400.0f, ((float)GetScreenHeight() / 2.0f) - 125.0f);
		box2Pos = Vector2(175.0f, ((float)GetScreenHeight() / 2.0f) - 125.0f);
		holdingBox1 = false;
		holdingBox2 = false;
		oldMousePos = Vector2();
	}

	void Update(CollisionDetection collisionDetection);
	void Render(CollisionDetection collisionDetection);
};

struct CircleLineSegmentCollisionSimulation
{
	Font font;
	Vector2 oldMousePos;

	Vector2 circlePos;
	Vector2 SegmentPos1;
	Vector2 SegmentPos2;
	const float circleRadius = 120.0f;
	bool holdingCircle;
	bool holdingLine;

	CircleLineSegmentCollisionSimulation(Font _font)
	{
		font = _font;
		circlePos = Vector2((float)GetScreenWidth() - 300.0f, ((float)GetScreenHeight() / 2.0f) - 50.0f);
		SegmentPos1 = Vector2(380.0f, ((float)GetScreenHeight() / 2.0f) + 100.0f);
		SegmentPos2 = Vector2(220.0f, ((float)GetScreenHeight() / 2.0f) - 200.0f);
		holdingCircle = false;
		holdingLine = false;
		oldMousePos = Vector2();
	}

	void Update(CollisionDetection collisionDetection);
	void Render(CollisionDetection collisionDetection);
};