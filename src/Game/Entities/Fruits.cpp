#include "Fruits.h"

Fruits::Fruits(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    switch (random)
    {
    case 0:
        sprite.cropFrom(spriteSheet,504+16,49,16,16);
        break;
    case 1:
        sprite.cropFrom(spriteSheet,504+32,49,16,16);
        break;
    case 2:
        sprite.cropFrom(spriteSheet,504+48,49,16,16);
        break;
    default:
        break;
    }
}