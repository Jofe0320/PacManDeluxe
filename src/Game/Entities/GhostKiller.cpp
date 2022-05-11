#include "GhostKiller.h"

GhostKiller::GhostKiller(int x, int y, int width, int height, ofImage spriteSheet): Entity(x, y, width, height){
    sprite.cropFrom(spriteSheet,599,48,16,16);
}