#pragma once

class GameObject{
    public:
        float x, y; //position

        void Draw();
        void Update();
        void CollisionDetection();
        GameObject(){}
        GameObject(float x, float y): x(x), y(y){}
};