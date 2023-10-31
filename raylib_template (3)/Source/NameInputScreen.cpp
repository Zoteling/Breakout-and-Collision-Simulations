#include "GamesResources.h"

void NameInputScreen::Update(GameState* gameState, Score* score)
{
    int key = GetCharPressed();

    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (letterCount < 3))
        {
            name[letterCount] = (char)key;
            name[letterCount + 1] = '\0';
            letterCount++;
        }

        key = GetCharPressed();
    }

    if ((letterCount >= 3))
    {
        *gameState = Menu;
        score->UpdateHighScores(name);
        score->SaveHighScores();

        score->score = 0;
        letterCount = 0;
        name[letterCount] = '\0';
    }
}

void NameInputScreen::Render()
{
    DrawTextureEx(backDropTexture, Vector2(((float)GetScreenWidth() / 2.0f) - 130.0f, ((float)GetScreenHeight() / 2.0f) - 6.0f), 0.0f, 1.5f, WHITE);

    Vector2 typeNamePos = Vector2(((float)GetScreenWidth() / 2.0f) - ((float)MeasureText("Type Name...", 35) / 2.0f), ((float)GetScreenHeight() / 2.0f) + 10.0f);
    Vector2 namePos = Vector2(((float)GetScreenWidth() / 2.0f) - ((float)MeasureText(name, 45) / 2.0f), ((float)GetScreenHeight() / 2.0f) + 8.0f);
    
    if (letterCount == 0)
    {
        DrawTextEx(font, "Type Name...", typeNamePos, 35, 1.0f, LIGHTGRAY);
    }
    else
    {
        DrawTextEx(font, name, namePos, 45.0f, 1.0f, DARKGRAY);
    }
}

