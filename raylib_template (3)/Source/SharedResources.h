#pragma once
#include "raylib.h"
#include "CollisionResources.h"

enum ProgramState
{
	Game,
	Simulation,
};

struct Background
{
	Texture2D texture;
	Texture2D textureBlue;
	Texture2D textureOrange;
	Rectangle source;
	const Rectangle destination = Rectangle(0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight());
	const Vector2 position = Vector2();
	const Vector2 scrollSpeed = Vector2(.1f, .1f);
	const float playerInfluence = .05f;


	Background(Texture2D _textureBlue, Texture2D _textureOrange)
	{
		texture = _textureBlue;
		textureBlue = _textureBlue;
		textureOrange = _textureOrange;
		source = Rectangle(0.0f, 0.0f, 64.0f, 64.0f);
	}

	void Update(float playerXPos);
	void Update();
	void Render();
};

struct StateController
{
	Texture2D buttonTexture;
	Font font;

	const Vector2 buttonSize = Vector2(260, 65);
	const Vector2 buttonPos = Vector2(20, 20);

	ProgramState state = Game;

	StateController(Texture2D _buttonTexture, Font _font)
	{
		buttonTexture = _buttonTexture;
		font = _font;
	}

	void Update(CollisionDetection collisionDetection, Background* background);
	void Render(CollisionDetection collisionDetection);
};