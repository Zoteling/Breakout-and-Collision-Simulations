#include "GamesResources.h"

void Block::Render()
{
	if (active)
	{
		DrawTextureEx(texture, position, 0, 1.8f, color);
	}
	else if (animationFrame < 11)
	{
		float frameWidth = 64;
		float frameHeight = 64;
		float Height = 384;
		DrawTexturePro(explosionSpriteSheet, Rectangle(frameWidth * animationFrame, Height, frameWidth, frameHeight),
			Rectangle(position.x + 20, position.y - 20, size.x + 40, size.y + 80), Vector2(32, 32), 0, WHITE);
		
		if (oddFrame)
		{
			animationFrame++;
		}

		oddFrame = !oddFrame;
	}
}