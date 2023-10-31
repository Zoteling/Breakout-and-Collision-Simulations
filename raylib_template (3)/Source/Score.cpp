#include "GamesResources.h"
#include <iostream>

void Score::UpdateHighScores(char name[4]) 
{

	for (int i = 0; i <= 4; i++)
	{
		if (score > highScore[i].score)
		{
			highScore[0].score = score;

			for (int j = 0; j < 4; j++)
			{
				highScore[0].name[j] = name[j];
			}
			break;
		}
	}
	BubbleSortHighScores();
}

void Score::DrawHighScores()
{
	float height = 320.0f;
	float spacing = 50.0f;
	Color shadowColor = Color(48, 131, 186, 255);

	for (int i = 4; i >= 0; i--)
	{
		const char highScoreName[9] = { highScore[i].name[0],
									highScore[i].name[1],
									highScore[i].name[2],
									' ', '-', ' ', '%', 'd' };

		float textX = ((float)GetScreenWidth() / 2.0f) - (MeasureTextEx(font, TextFormat(highScoreName, highScore[i].score), 40.0f, 1.0f).x / 2.0f);
		DrawTextEx(font, TextFormat(highScoreName, highScore[i].score), Vector2(textX, height + 4.0f), 40.0f, 1.0f, shadowColor);
		DrawTextEx(font, TextFormat(highScoreName, highScore[i].score), Vector2(textX, height), 40.0f, 1.0f, WHITE);
		height += spacing;
	}
}

void Score::DrawScore()
{
	Color textColor = Color(48, 131, 186, 255);
	Vector2 shadowPos = Vector2(((float)GetScreenWidth() / 2.0f) - ((float)MeasureText(TextFormat("%i", score), 80) / 2.0f), ((float)GetScreenHeight() / 2.0f) + 6.0f);
	Vector2 scorePos = Vector2(((float)GetScreenWidth() / 2.0f) - ((float)MeasureText(TextFormat("%i", score), 80) / 2.0f), (float)GetScreenHeight() / 2.0f);
	DrawTextEx(font, TextFormat("%i", score), shadowPos, 80.0f, 1.0f, textColor);
	DrawTextEx(font, TextFormat("%i", score), scorePos, 80.0f, 1.0f, WHITE);
}

void Score::LoadHighScores() 
{
	unsigned int dataSize;
	unsigned char* loadedData = LoadFileData("ScoreSaveData.txt", &dataSize);

	if (loadedData != nullptr && dataSize == sizeof(ScoreSaveData[5]))
	{
		memcpy(&highScore, loadedData, sizeof(ScoreSaveData[5]));
		free(loadedData);
	}
}

void Score::SaveHighScores()
{
	unsigned char data[sizeof(ScoreSaveData[5])];
	memcpy(data, &highScore, sizeof(ScoreSaveData[5]));
	SaveFileData("ScoreSaveData.txt", data, sizeof(data));
}

void Score::BubbleSortHighScores() 
{
	int x, y;
	bool switched;

	for (x = 0; x < 4; x++)
	{
		switched = false;
		for (y = 0; y < 4 - x; y++)
		{
			if (highScore[y].score > highScore[y + 1].score)
			{
				ScoreSaveData tempScoreData = highScore[y + 1];
				highScore[y + 1] = highScore[y];
				highScore[y] = tempScoreData;
				switched = true;
			}
		}
		if (switched == false) 
		{
			break;
		}
	}
}