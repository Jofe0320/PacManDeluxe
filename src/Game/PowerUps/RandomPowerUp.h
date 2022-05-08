#pragma once

#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"

class RandomPowerUp : public PowerUp{

public:
    void activate();
    int points =  rand()%50;

    Player *Pacman;
    EntityManager *em;
    RandomPowerUp(Player* Pac, EntityManager* em){
        this->Pacman  = Pac;
        this->em = em;
        this->setRank(1);
        this->setName("Point boost");
    }
    Player* getPacman();
    EntityManager* getEm();
    Entity* getRandomEntity();
};