#pragma once
#include "raylib.h"
#include "CollisionResources.h"

enum GameState
{
	Menu,
	InGame,
	NameInput,
	RestartMenu
};

struct Player
{
	Vector2 position;
	Vector2 oldPosition;
	Texture2D texture;
	const Vector2 size = Vector2(155.0f, 35.0f);
	const float speed = 6;

	Player(Texture2D _texture)
	{
		position = Vector2(((float)GetScreenWidth() / 2.0f) - (size.x / 2.0f), (float)GetScreenHeight() - 100.0f);
		oldPosition = Vector2();
		texture = _texture;
	}

	void Render();
	void Update();
};

struct ScoreSaveData
{
	char name[4] = {};
	int score = 0;

	ScoreSaveData(char _name[4], int _score)
	{
		score = _score;

		for (int i = 0; i < 4; i++)
		{
			name[i] = _name[i];
		}
	}
};

struct Score
{
	public:
		int score = 0;
		char defaultName[4] = { '-', '-', '-' };
		Font font;
		ScoreSaveData highScore[5] = { ScoreSaveData(defaultName, 0),
									   ScoreSaveData(defaultName, 0),
									   ScoreSaveData(defaultName, 0),
									   ScoreSaveData(defaultName, 0),
									   ScoreSaveData(defaultName, 0) };

		Score(Font _font)
		{
			font = _font;
		}

		void UpdateHighScores(char name[4]);
		void DrawHighScores();
		void DrawScore();
		void BubbleSortHighScores();
		void LoadHighScores();
		void SaveHighScores();
};

struct Block
{
	const Vector2 size = Vector2(115.0f, 58.0f);

	Texture2D texture;
	Vector2 position;
	Color color;
	bool active;

	Texture2D explosionSpriteSheet;
	int animationFrame;
	bool oddFrame = false;

	Block(Texture2D _texture, Texture2D _explosionSpriteSheet)
	{
		texture = _texture;
		position = Vector2((float)GetScreenWidth() / 4.0f, 150.0f);
		color = WHITE;
		active = true;
		explosionSpriteSheet = _explosionSpriteSheet;
		animationFrame = 0;
		oddFrame = false;
	}

	void Render();
};

struct Level
{
	const char* levelDataName = "level.txt";
	unsigned char* levelData;
	unsigned int levelFileSize;

	void LoadLevel(Block blocks[30]);
};

struct Ball
{
	Texture2D texture;
	Vector2 position;
	Vector2 speed;
	float speedMultiplier;
	const float speedMultiplierModifier = .0001f;
	const float radius = 20.0f;
	const float playerPosInfluence = .75f;

	Ball(Texture2D _texture)
	{
		texture = _texture;
		position = Vector2(((float)GetScreenWidth() / 2.0f), (float)GetScreenHeight() / 2.0f);
		speed = Vector2(0.0f, 6.0f);
		speedMultiplier = 1.0f;
	}

	void PlayerCollisions(CollisionDetection collisionDetection, Player* player);
	void BlockCollisions(CollisionDetection collisionDetection, Block blocks[30], Score* score, Level* level);
	void EdgeCollisions(Player* player, Block blocks[30], GameState* gameState, Level* level);
	void Update(CollisionDetection collisionDetection, Player* player, Block blocks[30], Score* score, GameState* gameState, Level* level);
	void Render();
};

struct MainMenu
{
	Font font;

	MainMenu(Font _font)
	{
		font = _font;
	}

	void Update(GameState* gameState);
	void Render();
};

struct NameInputScreen
{
	Font font;
	Texture2D backDropTexture;
	char name[4] = "\0";
	int letterCount = 0;

	NameInputScreen(Font _font, Texture2D _backDropTexture)
	{
		font = _font;
		backDropTexture = _backDropTexture;
	}

	void Update(GameState* gameState, Score* score);
	void Render();
};