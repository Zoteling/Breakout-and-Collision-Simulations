#include "SharedResources.h"
#include "CollisionResources.h"
#include "raylib.h"

void StateController::Update(CollisionDetection collisionDetection, Background* backGround)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());

	if (IsMouseButtonPressed(0))
	{
		if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, buttonPos, buttonSize))
		{
			if (state == Game)
			{
				state = Simulation;
				backGround->texture = backGround->textureOrange;
			}
			else if (state == Simulation)
			{
				state = Game;
				backGround->texture = backGround->textureBlue;
			}
		}
	}
}

void StateController::Render(CollisionDetection collisionDetection)
{
	Vector2 mousePos = Vector2((float)GetMouseX(), (float)GetMouseY());

	Color buttonColor = WHITE;
	Color textColor = GRAY;
	if (collisionDetection.CircleBoundingBox(mousePos, 1.0f, buttonPos, buttonSize))
	{
		buttonColor = LIGHTGRAY;
		textColor = DARKGRAY;
	}
	
	DrawTextureEx(buttonTexture, buttonPos, 0, 1.35f, buttonColor);
	DrawTextEx(font, "Switch Mode", Vector2(buttonPos.x + 30, buttonPos.y + 16), 30, 1.0f, textColor);
}