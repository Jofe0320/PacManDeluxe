#pragma once
#include "Player.h"
class PowerUp{
    private:
    Player* Pacman;
    public:
    PowerUp(){}
    Player* getPacman(){return Pacman;}
    void setPacman(Player* Pac){this->Pacman = Pac;}
    virtual void activate() = 0;

};