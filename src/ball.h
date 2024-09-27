#pragma once
#include "gameObject.h"

class Ball: public GameObject
{
public:
    int speed_x;
    int speed_y;
    int radius;
    int startSpeed;
    Sound win_sfx;

    Ball(){}
    Ball(float x, float y, int speedX, int speedY, int radius)
    : GameObject(x,y), speed_x(speedX), speed_y(speedY),radius(radius), startSpeed(speedX){}
    void Update(int *player1_score, int *player2_score, Sound sfx1, Sound sfx2);
    void Draw();
    void UpdateScore(int *player_score);
    void ResetBall();

};