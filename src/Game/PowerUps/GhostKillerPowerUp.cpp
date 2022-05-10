#include "GhostKillerPowerUp.h"
//Power Up that remove all Ghosts
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
// This loop eliminates the ghosts
for(Entity* entity:em->ghosts){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
                ghost->eyes = true;
    }
}