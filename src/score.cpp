#include <raylib.h>
#include "score.h"

void Score::Draw()
{
    DrawText(TextFormat("%i", value), x, y, 80, WHITE);    
}