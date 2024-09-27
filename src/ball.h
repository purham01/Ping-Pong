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
    Ball(float xn, float yn, int speedXn, int speedYn, int radiusn)
    : GameObject(xn,yn), speed_x(speedXn), speed_y(speedYn),radius(radiusn), startSpeed(speedXn){}
    void Update(int *player1_score, int *player2_score, Sound sfx1, Sound sfx2);
    void Draw();
    void UpdateScore(int *player_score);
    void ResetBall();

};