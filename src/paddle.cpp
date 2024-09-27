#include <raylib.h>
#include "paddle.h"


void Paddle::LimitMovement(){
    if (y <= 0){
        y = 0;
    }
    if (y + height >= GetScreenHeight())
    {
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw(){
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
}


void Player1Paddle::Update(){
    if(IsKeyDown(KEY_W)){
        y -= speed;
    }
    if(IsKeyDown(KEY_S)){
        y += speed;
    }

    LimitMovement();
}


void Player2Paddle::Update(){
    if(IsKeyDown(KEY_UP)){
        y -= speed;
    }
    if(IsKeyDown(KEY_DOWN)){
        y += speed;
    }

    LimitMovement();
}

void Player2Paddle::UpdateAI(int ball_x, int ball_y, int ball_speed_x)
{   
    framesCounter++;
    if((ball_speed_x > 0 && ball_x >= GetScreenWidth()/4) || (ball_speed_x < 0 && ball_x <= 3*GetScreenWidth()/4))
    {
        if(framesCounter > 15){
            if(y + height/2 > ball_y ){
                destination = ball_y - GetRandomValue(0,height/2);
            }

            else if(y + height/2 < ball_y ){
                destination = ball_y + GetRandomValue(0,height/2);
            }
            else
                destination = y;
            framesCounter = 0;
        }
        
        
        
        if(y + height/2 > destination){
            y = y - speed;
        }

        if(y+height/2 <= destination){
            y = y + speed;
        }

        LimitMovement();
    }
    
}

