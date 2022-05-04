#pragma once 
#include "Player.h"
#include "EntityManager.h"
class CherryPowerUp : public PowerUp{
    private:
    Player *Pacman;
    EntityManager *em;
    public:
    CherryPowerUp(Player* Pac, EntityManager* em){
        this->Pacman  = Pac;
        this->em = em;
        this->setRank(2);
    }
    Player* getPacman();
    EntityManager* getEm();
    Entity* getRandomEntity();
    void activate();
};