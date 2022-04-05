
#include "CherryPowerUp.h"

Player* CherryPowerUp::getPacman(){
    return this->Pacman;
}
EntityManager* CherryPowerUp::getEm(){
    return this-> em;
}
Entity* CherryPowerUp::getRandomEntity(){
    return this->getEm()->entities[ofRandom(0,this->getEm()->entities.size())];
}
void CherryPowerUp::activate(){
    this->getPacman()->setX(getRandomEntity()->getX());
    this->getPacman()->setY(getRandomEntity()->getY());
}



