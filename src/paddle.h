#pragma once
#include "gameObject.h"

class Paddle : public GameObject {
    protected:
        void LimitMovement();


    public:
        float width, height;
        int speed;
        
        Paddle(){}
        Paddle(float x, float y, float width, float height, int speed)
        : GameObject(x,y), width(width), height(height), speed(speed){}
        void Draw();
};

class Player1Paddle: public Paddle{
    public:
        void Update();
        Player1Paddle(){}
        Player1Paddle(float x, float y, float width, float height, int speed) :
            Paddle(x,y,width,height,speed) {}
};

class Player2Paddle: public Paddle{
    private:
        int framesCounter = 0;
        int destination = 0;
        
    public:
        void Update();
        void UpdateAI(int ball_x, int ball_y, int ball_speed_x);
        Player2Paddle(){}
        Player2Paddle(float x, float y, float width, float height, int speed) :
            Paddle(x,y,width,height,speed) {}
};
