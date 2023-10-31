#include "GamesResources.h"
#include "CollisionResources.h"
#include <cmath>

void Ball::PlayerCollisions(CollisionDetection collisionDetection, Player* player)
{
	if (collisionDetection.CircleBoundingBox(position, radius, player->position, player->size))
	{
		Vector2 playerMovement = Vector2(player->oldPosition.x - player->position.x, player->oldPosition.y - player->position.y);
		player->position.x += playerMovement.x;

		float playerCenterX = player->position.x + player->size.x / 2;
		float magnitude = sqrt(speed.x * speed.x + speed.y * speed.y);
		float posX = (position.x - playerCenterX) / (player->size.x / 2);
		speed.x = magnitude * posX * playerPosInfluence;
		speed.y = sqrt(magnitude * magnitude - speed.x * speed.x) * (speed.y > 0 ? -1 : 1);
	}
}

void Ball::BlockCollisions(CollisionDetection collisionDetection, Block blocks[30], Score* score, Level* level)
{
	for (int i = 0; i < 30; i++)
	{
		if (blocks[i].active && collisionDetection.CircleBoundingBox(position, radius, blocks[i].position, blocks[i].size))
		{
			blocks[i].active = false;
			score->score++;

			if (position.x >= blocks[i].position.x + blocks[i].size.x ||
				position.x <= blocks[i].position.x) {
				speed.x = -speed.x;
				speed.y = speed.y;
			}
			else
			{
				speed.x = speed.x;
				speed.y = -speed.y;
			}

			break;
		}
	}

	bool allBlocksGone = true;
	for (int i = 0; i < 30; i++)
	{
		if (blocks[i].active)
		{
			allBlocksGone = false;
		}
	}

	if (allBlocksGone)
	{
		position = Vector2(((float)GetScreenWidth() / 2.0f), (float)GetScreenHeight() / 2.0f);
		speed = Vector2(0.0f, 6.0f);
		level->LoadLevel(blocks);
	}
}

void Ball::EdgeCollisions(Player* player, Block blocks[30], GameState* gameState, Level* level)
{
	if (position.y >= GetScreenHeight() + radius)
	{
		*gameState = NameInput;
		speedMultiplier = 1.0f;
		position = Vector2(((float)GetScreenWidth() / 2.0f), (float)GetScreenHeight() / 2.0f);
		speed = Vector2(0.0f, 6.0f);
		player->position = Vector2(((float)GetScreenWidth() / 2.0f) - (player->size.x / 2.0f), (float)GetScreenHeight() - 100.0f);
		level->LoadLevel(blocks);
	}
	else if (position.y <= radius)
	{
		speed.x = speed.x;
		speed.y = -speed.y;
	}
	else if (position.x <= radius || position.x >= GetScreenWidth() - radius)
	{
		speed.x = -speed.x;
		speed.y = speed.y;
	}
}

void Ball::Update(CollisionDetection collisionDetection, Player* player, Block blocks[30], Score* score, GameState* gameState, Level* level)
{
	speedMultiplier += speedMultiplierModifier;

	position.x += speed.x * speedMultiplier;
	position.y += speed.y * speedMultiplier;

	PlayerCollisions(collisionDetection, player);
	BlockCollisions(collisionDetection, blocks, score, level);
	EdgeCollisions(player, blocks, gameState, level);
}

void Ball::Render()
{
	DrawTextureEx(texture, Vector2(position.x - radius, position.y - radius), 0, 1.8f, WHITE);
}