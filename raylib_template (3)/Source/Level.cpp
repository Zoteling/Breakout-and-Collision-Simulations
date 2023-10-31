#include "GamesResources.h"

void Level::LoadLevel(Block blocks[30])
{
	levelFileSize = 0;
	levelData = nullptr;
	levelData = LoadFileData(levelDataName, &levelFileSize);

	if (levelData != nullptr)
	{
		int startX = 50;
		int currentX = startX;
		int currentY = 50;
		int YposModifier = 100;
		int XposModifier = 110;
		int blockInt = 0;

		for (unsigned int i = 0; i < levelFileSize; i++)
		{
			if (levelData[i] == 'a' || levelData[i] == 'b' || levelData[i] == 'c')
			{
				if (levelData[i] == 'a') 
				{ 
					blocks[blockInt].color = WHITE; 
				}
				if (levelData[i] == 'c') 
				{ 
					blocks[blockInt].color = RAYWHITE; 
				}
				if (levelData[i] == 'c') 
				{ 
					blocks[blockInt].color = LIGHTGRAY; 
				}

				blocks[blockInt].position.x = (float)currentX;
				blocks[blockInt].position.y = (float)currentY;
				blocks[blockInt].active = true;
				blocks[blockInt].animationFrame = 0;
				blocks[blockInt].oddFrame = false;
				currentX += XposModifier;
				blockInt++;
			}
			else if (levelData[i] == ' ') 
			{ 
				currentX += XposModifier; 
			}
			else if (levelData[i] == '\n') 
			{ 
				currentY += YposModifier; currentX = startX; 
			}
		}

		UnloadFileData(levelData);
	}
}