#pragma once
#include "gameObject.h"

class Score: public GameObject
{
    public: 
        int value;

        Score(){}
        Score(float x,float y, int value) : GameObject(x,y), value(value) {}

        void Draw();
};