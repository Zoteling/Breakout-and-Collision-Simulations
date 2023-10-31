#include "CollisionResources.h"
#include "raylib.h"

void CollisionSimulationButtons::Update(CollisionDetection collisionDetection, SimulationState* state)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 buttonSize = Vector2(buttonWidth, buttonHeight);

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleCircleButtonPos, buttonSize))
		{
			*state = CircleCircleSim;
		}
		else if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleBoundingBoxButtonPos, buttonSize))
		{
			*state = CircleBoundingBoxSim;
		}
		else if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, boundingBoxBoundingBoxButtonPos, buttonSize))
		{
			*state = BoundingBoxBoundingBoxSim;
		}
		else if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleLineSegmentButtonPos, buttonSize))
		{
			*state = CircleLineSegmentSim;
		}
	}
}

void CollisionSimulationButtons::Render(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 buttonSize = Vector2(buttonWidth, buttonHeight);

	Color circleCircleButtonColor = WHITE;
	Color circleCircleTextColor = GRAY;
	if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleCircleButtonPos, buttonSize)) 
	{ 
		circleCircleButtonColor = LIGHTGRAY; circleCircleTextColor = DARKGRAY; 
	}
	DrawTextureEx(buttonTexture, circleCircleButtonPos, 0, 1.35f, circleCircleButtonColor);
	DrawTextEx(font, "Circle Circle Sim", Vector2(circleCircleButtonPos.x + 15, circleCircleButtonPos.y + 20), 25.0f, 1.0f, circleCircleTextColor);

	Color circleBoxButtonColor = WHITE;
	Color circleBoxTextColor = GRAY;
	if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleBoundingBoxButtonPos, buttonSize)) 
	{ 
		circleBoxButtonColor = LIGHTGRAY; circleBoxTextColor = DARKGRAY; 
	}
	DrawTextureEx(buttonTexture, circleBoundingBoxButtonPos, 0, 1.35f, circleBoxButtonColor);
	DrawTextEx(font, "Circle Box Sim", Vector2(circleBoundingBoxButtonPos.x + 30, circleBoundingBoxButtonPos.y + 20), 25.0f, 1.0f, circleBoxTextColor);

	Color boxBoxButtonColor = WHITE;
	Color boxBoxTextColor = GRAY;
	if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, boundingBoxBoundingBoxButtonPos, buttonSize)) 
	{ 
		boxBoxButtonColor = LIGHTGRAY; boxBoxTextColor = DARKGRAY; 
	}
	DrawTextureEx(buttonTexture, boundingBoxBoundingBoxButtonPos, 0, 1.35f, boxBoxButtonColor);
	DrawTextEx(font, "Box Box Sim", Vector2(boundingBoxBoundingBoxButtonPos.x + 50, boundingBoxBoundingBoxButtonPos.y + 20), 25.0f, 1.0f, boxBoxTextColor);

	Color circleLineButtonColor = WHITE;
	Color circleLineTextColor = GRAY;
	if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, circleLineSegmentButtonPos, buttonSize)) 
	{ 
		circleLineButtonColor = LIGHTGRAY; circleLineTextColor = DARKGRAY; 
	}
	DrawTextureEx(buttonTexture, circleLineSegmentButtonPos, 0, 1.35f, circleLineButtonColor);
	DrawTextEx(font, "Circle Line Sim", Vector2(circleLineSegmentButtonPos.x + 30, circleLineSegmentButtonPos.y + 20), 25.0f, 1.0f, circleLineTextColor);
}

void CircleCircleCollisionSimulation::Update(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 mouseDelta = Vector2((float)GetMouseX() - oldMousePos.x, (float)GetMouseY() - oldMousePos.y);

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleCircle(mousePos, 1.0f, circle1Pos, circle1Radius))
		{
			holdingCircle1 = true;
		}
		else if (collisionDetection.CircleCircle(mousePos, 1.0f, circle2Pos, circle2Radius))
		{
			holdingCircle2 = true;
		}
	}
	else if (IsMouseButtonReleased(0))
	{
		holdingCircle1 = false;
		holdingCircle2 = false;
	}

	if (holdingCircle1)
	{
		circle1Pos = Vector2(circle1Pos.x + mouseDelta.x, circle1Pos.y + mouseDelta.y);
	}
	else if (holdingCircle2)
	{
		circle2Pos = Vector2(circle2Pos.x + mouseDelta.x, circle2Pos.y + mouseDelta.y);
	}

	oldMousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
}

void CircleCircleCollisionSimulation::Render(CollisionDetection collisionDetection)
{
	Color shadowColor = Color(158, 104, 51, 255);

	DrawCircle((int)circle1Pos.x, (int)circle1Pos.y + 6, circle1Radius, shadowColor);
	DrawCircle((int)circle2Pos.x, (int)circle2Pos.y + 6, circle2Radius, shadowColor);
	DrawCircle((int)circle1Pos.x, (int)circle1Pos.y, circle1Radius, WHITE);
	DrawCircle((int)circle2Pos.x, (int)circle2Pos.y, circle2Radius, WHITE);

	if (collisionDetection.CircleCircle(circle1Pos, circle1Radius, circle2Pos, circle2Radius))
	{
		DrawTextEx(font, "Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
	else
	{
		DrawTextEx(font, "Not Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Not Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
}

void CircleBoundingBoxCollisionSimulation::Update(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 mouseDelta = Vector2((float)GetMouseX() - oldMousePos.x, (float)GetMouseY() - oldMousePos.y);

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleCircle(mousePos, 1.0f, circlePos, circleRadius))
		{
			holdingCircle = true;
		}
		else if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, boxPos, boxSize))
		{
			holdingBox = true;
		}
	}
	else if (IsMouseButtonReleased(0))
	{
		holdingCircle = false;
		holdingBox = false;
	}

	if (holdingCircle)
	{
		circlePos = Vector2(circlePos.x + mouseDelta.x, circlePos.y + mouseDelta.y);
	}
	else if (holdingBox)
	{
		boxPos = Vector2(boxPos.x + mouseDelta.x, boxPos.y + mouseDelta.y);
	}

	oldMousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
}

void CircleBoundingBoxCollisionSimulation::Render(CollisionDetection collisionDetection)
{
	Color shadowColor = Color(158, 104, 51, 255);

	DrawCircle((int)circlePos.x, (int)circlePos.y + 6, circleRadius, shadowColor);
	DrawRectangle((int)boxPos.x, (int)boxPos.y + 6, (int)boxSize.x, (int)boxSize.y, shadowColor);
	DrawCircle((int)circlePos.x, (int)circlePos.y, circleRadius, WHITE);
	DrawRectangle((int)boxPos.x, (int)boxPos.y, (int)boxSize.x, (int)boxSize.y, WHITE);

	if (collisionDetection.CircleBoundingBox(circlePos, circleRadius, boxPos, boxSize)) 
	{
		DrawTextEx(font, "Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
	else
	{
		DrawTextEx(font, "Not Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Not Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
}

void BoundingBoxBoundingBoxCollisionSimulation::Update(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 mouseDelta = Vector2((float)GetMouseX() - oldMousePos.x, (float)GetMouseY() - oldMousePos.y);

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, box1Pos, box1Pos))
		{
			holdingBox1 = true;
		}
		else if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, box2Pos, box2Size))
		{
			holdingBox2 = true;
		}
	}
	else if (IsMouseButtonReleased(0))
	{
		holdingBox1 = false;
		holdingBox2 = false;
	}

	if (holdingBox1)
	{
		box1Pos = Vector2(box1Pos.x + mouseDelta.x, box1Pos.y + mouseDelta.y);
	}
	else if (holdingBox2)
	{
		box2Pos = Vector2(box2Pos.x + mouseDelta.x, box2Pos.y + mouseDelta.y);
	}

	oldMousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
}

void BoundingBoxBoundingBoxCollisionSimulation::Render(CollisionDetection collisionDetection)
{
	Color shadowColor = Color(158, 104, 51, 255);

	DrawRectangle((int)box1Pos.x, (int)box1Pos.y + 6, (int)box1Size.x, (int)box1Size.y, shadowColor);
	DrawRectangle((int)box2Pos.x, (int)box2Pos.y + 6, (int)box2Size.x, (int)box2Size.y, shadowColor);
	DrawRectangle((int)box1Pos.x, (int)box1Pos.y, (int)box1Size.x, (int)box1Size.y, WHITE);
	DrawRectangle((int)box2Pos.x, (int)box2Pos.y, (int)box2Size.x, (int)box2Size.y, WHITE);

	if (collisionDetection.BoundingBoxBoundingBox(box1Pos, box1Size, box2Pos, box2Size)) 
	{
		DrawTextEx(font, "Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
	else
	{
		DrawTextEx(font, "Not Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Not Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
}

void CircleLineSegmentCollisionSimulation::Update(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
	Vector2 mouseDelta = Vector2((float)GetMouseX() - oldMousePos.x, (float)GetMouseY() - oldMousePos.y);

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleCircle(mousePos, 1.0f, circlePos, circleRadius))
		{
			holdingCircle = true;
		}
		else if (collisionDetection.CircleLineSegment(mousePos, 10.0f, SegmentPos1, SegmentPos2))
		{
			holdingLine = true;
		}
	}
	else if (IsMouseButtonReleased(0))
	{
		holdingCircle = false;
		holdingLine = false;
	}

	if (holdingCircle) 
	{
		circlePos = Vector2(circlePos.x + mouseDelta.x, circlePos.y + mouseDelta.y);
	}
	if (holdingLine) 
	{
		SegmentPos1 = Vector2(SegmentPos1.x + mouseDelta.x, SegmentPos1.y + mouseDelta.y);
		SegmentPos2 = Vector2(SegmentPos2.x + mouseDelta.x, SegmentPos2.y + mouseDelta.y);
	}

	oldMousePos = Vector2((float)GetMouseX(), (float)GetMouseY());
}

void CircleLineSegmentCollisionSimulation::Render(CollisionDetection collisionDetection)
{
	Color shadowColor = Color(158, 104, 51, 255);

	DrawCircle((int)circlePos.x, (int)circlePos.y + 6, circleRadius, shadowColor);
	DrawLineEx(Vector2(SegmentPos1.x, SegmentPos1.y + 6.0f), Vector2(SegmentPos2.x, SegmentPos2.y + 6.0f), 3.0f, shadowColor);
	DrawCircle((int)circlePos.x, (int)circlePos.y, circleRadius, WHITE);
	DrawLineEx(SegmentPos1, SegmentPos2, 3.0f, WHITE);

	if (collisionDetection.CircleLineSegment(circlePos, circleRadius, SegmentPos1, SegmentPos2)) 
	{
		DrawTextEx(font, "Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
	else
	{
		DrawTextEx(font, "Not Colliding!", Vector2(28, 99), 30, 1.0f, shadowColor);
		DrawTextEx(font, "Not Colliding!", Vector2(28, 95), 30, 1.0f, WHITE);
	}
}