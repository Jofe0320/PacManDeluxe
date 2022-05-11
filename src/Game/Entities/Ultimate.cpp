#include "Ultimate.h"

Ultimate::Ultimate(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,568,49,16,16);
}