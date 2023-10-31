#include "SharedResources.h"

void Background::Update(float playerXPos)
{
	source.x = playerXPos * playerInfluence;
	source.y += scrollSpeed.y;
}

void Background::Update()
{
	source.y += scrollSpeed.y;
}

void Background::Render()
{
	DrawTextureTiled(texture, source, destination, position, 0, 2, WHITE);
}