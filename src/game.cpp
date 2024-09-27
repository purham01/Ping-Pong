#include <raylib.h>
#include <iostream>
#include "game.h"
#include "ball.h"
#include "paddle.h"
#include "score.h"

using namespace std;

void Game::StartGame(void){

    cout << "Starting the game" << endl;
    InitWindow(screen_width, screen_height, "Pong!");       //Initialise window
    InitAudioDevice();      // Initialize audio device
    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    UnloadGame();         // Unload loaded data (textures, sounds, models)
    CloseAudioDevice();     // Close audio device
    CloseWindow();        // Close window and OpenGL context
}

//initisialising all the data for the game
void Game::InitGame(void)
{
    int paddle_height = 120;
    int paddle_width = 25;

    ball = Ball(screen_width/2, screen_width/2, 10, 10, 20);
    player1 = Player1Paddle(10, screen_height/2 - paddle_height/2, paddle_width, paddle_height, 6);
    player2 = Player2Paddle(screen_width - paddle_width - 10, screen_height/2 - paddle_height/2, paddle_width, paddle_height, player2_speed);
    
    player1_score = Score(screen_width/4 - 20, 20, 0);
    player2_score = Score(3*screen_width/4 - 20, 20, 0);
    
    sfx1 = LoadSound("resources/Ping.wav");
    SetSoundPan(sfx1, 0.6);
    sfx2 = LoadSound("resources/Pong.wav");
    SetSoundPan(sfx2, 0.4);

    ball.win_sfx = LoadSound("resources/win.wav");
    
    ball.ResetBall();
}

void Game::Gameplay(void)
{
    framesCounter++;

    if(framesCounter > 240 ){ //waiting for countdown timer

        ball.Update(&player1_score.value, &player2_score.value, sfx1, sfx2);
        player1.Update();
        
        if (gameType) //Update based on if we're playing PvP or PvE
            player2.Update();
        else
            player2.UpdateAI(ball.x,ball.y,ball.speed_x);

        //Checking for collisions
        if(CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius, 
        Rectangle{player1.x, player1.y, player1.width, player1.height})){        
            ball.speed_x *= -1;

            if (ball.speed_x < 40) //increase ball speed with each bounce, if speed reaches 30, the player who scores gets 10 points instead of one (starting speed 10, max 40)
                ball.speed_x += 1;

            ball.speed_y = (ball.y - player1.height/2 - player1.y)/(player1.height)*8; //bounce depending on the distance from middle of paddle
            
            PlaySound(sfx1);
        }

        if(CheckCollisionCircleRec(Vector2{(float)ball.x, (float)ball.y}, ball.radius, 
        Rectangle{player2.x, player2.y, player2.width, player2.height})){
            ball.speed_x *= -1;

            if (ball.speed_x > -40)
                ball.speed_x -= 1;

            ball.speed_y = (ball.y - player2.height/2 - player2.y)/(player2.height/2)*8;

            PlaySound(sfx2);
        }
    }
}

void Game::UpdateGame(void)
{
    //simple scene manager
    switch (currentScreen)
    {
        case MAIN_MENU:
        {
            if (IsKeyPressed(KEY_Q))
            {
                gameType = 1;
                InitGame();
                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_E))
            {
                gameType = 0;
                currentScreen = DIFFICULTY;
            }
        }
        break;

        //difficulty selection for PvE
        case DIFFICULTY:
        {
            if (IsKeyPressed(KEY_Q))
            {
                player2_speed = 2;
                InitGame();
                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_W))
            {
                player2_speed = 4;
                InitGame();
                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_E))
            {
                player2_speed = 6;
                InitGame();
                currentScreen = GAMEPLAY;
            }

        }
        break;

        //gameplay loop
        case GAMEPLAY: 
        {   
            Gameplay();
        }
    }

    

}

void Game::DrawGame(void)
{
    BeginDrawing();

    //background
    ClearBackground(Color{51, 63, 88, 255});
    DrawRectangle(screen_width/2, 0, screen_width/2, screen_height,  Color{74, 122, 150, 255});
    DrawCircle(screen_width/2, screen_height/2, 150, Color{110, 181, 204, 255});
    DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);


    switch (currentScreen)
    {
        case MAIN_MENU:
        {
            DrawText("PONG!", 40, 40, 60, WHITE);
            DrawText("Q - PLAY PvP", 120, 220, 40, WHITE);
            DrawText("E - PLAY PvE", 120, 270, 40, WHITE);
            DrawText("ESC - QUIT", 120, 320, 40, WHITE);
        }
        break;

        case DIFFICULTY:
        {
            DrawText("PONG!", 40, 40, 60, WHITE);
            DrawText("Q - EASY", 120, 220, 40, WHITE);
            DrawText("W - NORMAL", 120, 270, 40, WHITE);
            DrawText("E - HARD", 120, 320, 40, WHITE);
        }
        break;

        case GAMEPLAY: 
        {
            //controls for the first 10 seconds
            DrawUI();

            //gameplay
            ball.Draw();
            player1.Draw();
            player2.Draw();
            
            //score
            player1_score.Draw();
            player2_score.Draw();

            //drawing intro countdown
            DrawCounter();
        }
    }
    

    EndDrawing();
}

void Game::DrawUI(void)
{
    
    if (framesCounter < 10*60){
        DrawText("W", 80, player1.y - 40, 70, LIGHTGRAY); //300
        DrawText("S", 80, player1.y + 80, 70, LIGHTGRAY);        //420

        if (gameType) //only shown in PvP
        {
            DrawTriangle((Vector2){ screen_width -100.0f , player2.y - 40 }, //300
                    (Vector2){ screen_width -120.0f , player2.y },      //340
                    (Vector2){ screen_width -80.0f , player2.y }, LIGHTGRAY);
            DrawRectangle(screen_width -105.0f,player2.y, 10, 30, LIGHTGRAY);

        
            DrawTriangle((Vector2){ screen_width -120.0f , player2.y + 110 }, //450
                    (Vector2){ screen_width -100.0f , player2.y + 150 },         //490
                    (Vector2){ screen_width -80.0f , player2.y + 110  }, LIGHTGRAY);
            DrawRectangle(screen_width -105.0f,player2.y + 80, 10, 30, LIGHTGRAY); //420
        }
        
    }
}

void Game::DrawCounter(void)
{
    if (framesCounter < 60) DrawText("3", screen_width/2 - 20, screen_height/2 - 40, 80, WHITE);
    else if (framesCounter < 120) DrawText("2", screen_width/2 - 20, screen_height/2 - 40, 80, WHITE);
    else if (framesCounter < 180) DrawText("1", screen_width/2 - 10, screen_height/2 - 40, 80, WHITE);
    else if (framesCounter < 240) DrawText("GO!", screen_width/2 - 55, screen_height/2 - 40, 80, WHITE);
}


// Unload game variables
void Game::UnloadGame(void)
{
    if (currentScreen == GAMEPLAY){
        UnloadSound(sfx1);
        UnloadSound(sfx2);
        UnloadSound(ball.win_sfx);
    }
}

// Update and Draw (one frame)
void Game::UpdateDrawFrame()
{
    UpdateGame();
    DrawGame();
}



