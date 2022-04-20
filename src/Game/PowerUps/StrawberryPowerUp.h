#include "Player.h"
#include "EntityManager.h"
#include "Entity.h"


class StrawberryPowerUp: public PowerUp{
    private:
    Player *Pacman;
    EntityManager *em;
    public:
    StrawberryPowerUp(Player* Pac, EntityManager* em){
        this->Pacman  = Pac;
        this->em = em;
    }
    Player* getPacman(){
        return this->Pacman;
    }
    EntityManager* getEm(){
        return this->em;
    }
    //Activate a counter that on player.cpp would make pacman invicible and invencible for certain steps
    void activate(){
        this->getPacman()->StrawStepCounter = 0;
    }
};