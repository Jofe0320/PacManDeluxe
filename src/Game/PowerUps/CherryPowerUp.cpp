
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
    Entity* Position = getRandomEntity();
    this->getPacman()->setX(Position->getX());
    this->getPacman()->setY(Position->getY());
}



