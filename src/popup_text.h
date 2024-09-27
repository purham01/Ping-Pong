#pragma once
#include "gameObject.h"
#include <string>

class PopupText : public GameObject{
    public:
        float transAlpha = 0.0;
        const char *text;

        PopupText(){};
        PopupText(const char *text): GameObject(0,0), text(text){};
        void Draw();
        void Spawn(int xn, int yn);
};