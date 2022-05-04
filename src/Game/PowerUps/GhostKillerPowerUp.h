#pragma once

#include "PowerUp.h"
#include "EntityManager.h"
#include "Player.h"
#include "Ghost.h"
#include "entity.h"

class GhostKillerPowerUp : public PowerUp{

    int points =  rand()%50;
    
public:
    void activate();

    Player *Pacman;
    EntityManager *em;
    GhostKillerPowerUp(Player* Pac, EntityManager* em){
        this->Pacman  = Pac;
        this->em = em;
        this->setRank(4);
    }
    Player* getPacman();
    EntityManager* getEm();
    Entity* getRandomEntity();
    Entity* getGhosts();
};