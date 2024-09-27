#include <raylib.h>
#include "ball.h"
#include "game.h"
#include <math.h>

void Ball::Draw(){
    DrawCircle(x, y, radius, Color{238, 134, 149, 255});
}

void Ball::Update(int *player1_score, int *player2_score, Sound sfx1, Sound sfx2)
{
    x += speed_x;
    y += speed_y;

    if(y+radius >= GetScreenHeight() || y - radius <= 0){
        speed_y *= -1;
        Sound sound_choices[2] = {sfx1,sfx2};

        PlaySound(sound_choices[GetRandomValue(0,1)]);
    }

    if(x - radius <= 0)
    {   
        UpdateScore(player2_score);
    }

    if(x + radius >= GetScreenWidth()){
        UpdateScore(player1_score);
    }
}

void Ball::UpdateScore(int *player_score){
    if (abs(speed_x) >= 30)
        {
            (*player_score)+=10;
        }
        else
            (*player_score)++;
        PlaySound(win_sfx);
        ResetBall();
}


void Ball::ResetBall()
{
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speed_choices[2] = {-1,1};
    speed_x = startSpeed;
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y = 0;
}