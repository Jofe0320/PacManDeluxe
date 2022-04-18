#pragma once

#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class RandomPowerUp : public PowerUp{

public:
    void activate();
    int points;

    Player *Pacman;
    EntityManager *em;
    RandomPowerUp(Player* Pac, EntityManager* em){
        this->Pacman  = Pac;
        this->em = em;
    }
    Player* getPacman();
    EntityManager* getEm();
    Entity* getRandomEntity();
};