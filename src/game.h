#pragma once

#include <raylib.h>
#include "ball.h"
#include "paddle.h"
#include "score.h"

class Game{
    private:
        typedef enum GameScreen { MAIN_MENU=0, DIFFICULTY, GAMEPLAY } GameScreen;
        const int screen_width = 1280;
        const int screen_height = 800;

        //game objects
        Ball ball;
        Player1Paddle player1;
        Player2Paddle player2;
        Sound sfx1,sfx2;
        Score player1_score, player2_score;

        //game variables
        bool gameType = 0;
        int player2_speed = 6;
        int framesCounter = 0;
        GameScreen currentScreen = MAIN_MENU;


        // Initialise game
        void InitGame(void); 
        // Update game (one frame)
        void UpdateGame(void);   
        // Draw game (one frame)
        void DrawGame(void);         
        // Unload game
        void UnloadGame(void);      
        // Update and Draw (one frame)
        void UpdateDrawFrame(void);  
        //UI
        void DrawUI(void);
        void DrawCounter(void);
        //Gameplay loop
        void Gameplay(void);

    public:
        //default constructor
        Game(){} 
        // Start game
        void StartGame(void);   

};
