#include "SharedResources.h"
#include "GamesResources.h"
#include "raylib.h"

void Player::Update()
{
	oldPosition = position;

	if (IsKeyDown(KEY_LEFT) && position.x >= 0)
	{
		position.x -= speed;
	}
	else if (IsKeyDown(KEY_RIGHT) && position.x <= GetScreenWidth() - size.x)
	{
		position.x += speed;
	}
}

void Player::Render()
{
	DrawTextureEx(texture, position, 0, 1.5f, WHITE);
}

