#include "GamesResources.h"

void MainMenu::Update(GameState* gameState)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		*gameState = InGame;
	}
}

void MainMenu::Render()
{
	Color shadowColor = Color(48, 131, 186, 255);

	//Title
	Vector2 titleShadowPos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "BREAKOUT!", 80, 1.0f).x / 2), 156);
	Vector2 titlePos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "BREAKOUT!", 80, 1.0f).x / 2), 150);
	DrawTextEx(font, "BREAKOUT!", titleShadowPos, 80.0f, 1.0f, shadowColor);
	DrawTextEx(font, "BREAKOUT!", titlePos, 80.0f, 1.0f, WHITE);
	
	//Press Space
	Vector2 textShadowPos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "Press Space To Play!", 40, 1.0f).x / 2), (float)GetScreenHeight() - 196.0f);
	Vector2 textPos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "Press Space To Play!", 40, 1.0f).x / 2), (float)GetScreenHeight() - 200.0f);
	DrawTextEx(font, "Press Space To Play!", textShadowPos, 40.0f, 1.0f, shadowColor);
	DrawTextEx(font, "Press Space To Play!", textPos, 40.0f, 1.0f, WHITE);

	//High Scores Header
	Vector2 scoreHeaderShadowPos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "High Scores:", 40, 1.0f).x / 2), 254);
	Vector2 scoreHeaderPos = Vector2((GetScreenWidth() / 2) - (MeasureTextEx(font, "High Scores:", 40, 1.0f).x / 2), 250);
	DrawTextEx(font, "High Scores:", scoreHeaderShadowPos, 40.0f, 1.0f, shadowColor);
	DrawTextEx(font, "High Scores:", scoreHeaderPos, 40.0f, 1.0f, WHITE);
}