#include "popup_text.h"
#include <raylib.h>

void PopupText::Draw()
{
    transAlpha -= 0.02f;
    DrawText(TextFormat("%s",text), x, y, 20, Fade(LIGHTGRAY, transAlpha));   
}

void PopupText::Spawn(int xn, int yn)
{
    x = xn;
    y = yn;
    transAlpha = 1.0;
}
