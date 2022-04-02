#pragma once
#include"PowerUp.h"

class EatingTime : public PowerUp{
    public:
    EatingTime(Player* Pac){
        this->setPacman(Pac);
    }
    void activate();

};