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
    }
    Player* getPacman(){
        return this->Pacman;
    }
    EntityManager* getEm(){
        return this-> em;
    }
    Entity* getRandomEntity(){
        return this->getEm()->entities[ofRandom(0,this->getEm()->entities.size())];
    }
    void activate(){
       this->getPacman()->setX(getRandomEntity()->getX());
       this->getPacman()->setY(getRandomEntity()->getY());
    }
};