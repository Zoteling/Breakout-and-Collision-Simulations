/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*b
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "CollisionResources.h"
#include "GamesResources.h"
#include "SharedResources.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------

    InitAudioDevice();

    auto sound = LoadSound("./hitHurt.ogg");

    //Initialize Shared
    Font font = LoadFont("CustomFont.ttf");
    Texture2D buttonTexture = LoadTexture("Button.png");
    StateController stateController = StateController(buttonTexture, font);

    //Initialize Simulation
    CollisionDetection collisionDetection = {};
    CollisionSimulationButtons collisionButtons = CollisionSimulationButtons(buttonTexture, font);
    CircleCircleCollisionSimulation circleCircleSim = CircleCircleCollisionSimulation(font);
    CircleBoundingBoxCollisionSimulation circleBoundingBoxSim = CircleBoundingBoxCollisionSimulation(font);
    BoundingBoxBoundingBoxCollisionSimulation boundingBoxBoundingBoxSim = BoundingBoxBoundingBoxCollisionSimulation(font);
    CircleLineSegmentCollisionSimulation circleLineSim = CircleLineSegmentCollisionSimulation(font);
    SimulationState simState = CircleCircleSim;

    //Initialize Game
    Score score = Score(font);
    score.LoadHighScores();
    MainMenu mainMenu = MainMenu(font);
    NameInputScreen nameInput = NameInputScreen(font, buttonTexture);
    GameState gameState = Menu;
    Player player = Player(LoadTexture("Paddle.png"));
    Ball ball = Ball(LoadTexture("Ball.png"));
    Background background = Background(LoadTexture("Background Blue.png"), LoadTexture("Background Brown.png"));

    Block block = Block(LoadTexture("Block.png"), LoadTexture("ExplosionSpriteSheet.png"));
    Block blocks[30] = 
    { 
        block, block, block, block, block, block, block, block, block, block,
        block, block, block, block, block, block, block, block, block, block,
        block, block, block, block, block, block, block, block, block, block 
    };

    Level level = Level();
    level.LoadLevel(blocks);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        if (stateController.state == Game)
        {
            if (gameState == Menu)
            {
                background.Update();
                background.Render();

                score.DrawHighScores();

                mainMenu.Update(&gameState);
                mainMenu.Render();
            }
            else if (gameState == InGame)
            {
                background.Update(player.position.x);
                background.Render();

                score.DrawScore();

                player.Update();
                player.Render();

                ball.Update(collisionDetection, &player, blocks, &score, &gameState, &level);
                ball.Render();

                for (int i = 0; i < 30; i++) 
                { 
                    blocks[i].Render(); 
                }
            }
            else if (gameState == NameInput)
            {
                background.Update();
                background.Render();

                nameInput.Update(&gameState, &score);
                nameInput.Render();
            }
        }
        else if (stateController.state == Simulation)
        {
            background.Update();
            background.Render();

            collisionButtons.Update(collisionDetection, &simState);
            collisionButtons.Render(collisionDetection);

            if (simState == CircleCircleSim)
            {
                circleCircleSim.Update(collisionDetection);
                circleCircleSim.Render(collisionDetection);
            }
            else if (simState == CircleBoundingBoxSim)
            {
                circleBoundingBoxSim.Update(collisionDetection);
                circleBoundingBoxSim.Render(collisionDetection);
            }
            else if (simState == BoundingBoxBoundingBoxSim)
            {
                boundingBoxBoundingBoxSim.Update(collisionDetection);
                boundingBoxBoundingBoxSim.Render(collisionDetection);
            }
            else if (simState == CircleLineSegmentSim)
            {
                circleLineSim.Update(collisionDetection);
                circleLineSim.Render(collisionDetection);
            }
        }

        stateController.Update(collisionDetection, &background);
        stateController.Render(collisionDetection);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseAudioDevice();
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}