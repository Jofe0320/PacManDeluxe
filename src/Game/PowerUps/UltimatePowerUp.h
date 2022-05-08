#pragma once

#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class UltimatePowerUp : public PowerUp{

private:
Player *Pacman;
public:
    void activate();
    UltimatePowerUp(Player* Pac){
        this->Pacman  = Pac;
        this->setRank(5);
        this->setName("Ultimate");
    }
    Player* getPacman();
};