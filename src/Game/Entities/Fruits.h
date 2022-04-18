#pragma once

#include "Entity.h"
#include "ofImage.h"

class Fruits: public Entity{
    public:
        Fruits(int, int, int, int, ofImage);
        int random = rand()%3;
};
