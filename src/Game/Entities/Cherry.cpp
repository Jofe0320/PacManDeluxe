#include "Cherry.h"
// Decided to seperate the object from the powerUp for organization
Cherry::Cherry(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,488,49,16,16);
}