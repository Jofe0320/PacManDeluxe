#include "GhostKillerPowerUp.h"

Player* GhostKillerPowerUp::getPacman(){
    return this->Pacman;
}
EntityManager* GhostKillerPowerUp::getEm(){
    return this-> em;
}
Entity* GhostKillerPowerUp::getRandomEntity(){
    return this->getEm()->entities[ofRandom(0,this->getEm()->entities.size())];
}

void GhostKillerPowerUp::activate(){
    EntityManager* em = getEm();

for(Entity* entity:em->ghosts){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
                ghost->remove = true;
    }
}