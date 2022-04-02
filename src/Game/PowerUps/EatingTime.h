#pragma once
#include"PowerUp.h"
#include "Player.h"

class EatingTime : public PowerUp{
    private:
    Player *Pacman;
    public:
    EatingTime(Player* Pac){
        this->Pacman  = Pac;
    }
    Player* getPacman();
    void activate();

};