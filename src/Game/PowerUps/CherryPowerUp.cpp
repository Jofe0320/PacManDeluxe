
#include "CherryPowerUp.h"

Player* CherryPowerUp::getPacman(){
    return this->Pacman;
}
EntityManager* CherryPowerUp::getEm(){
    return this-> em;
}
Entity* CherryPowerUp::getRandomEntity(){
    return this->getEm()->entities[ofRandom(0,this->getEm()->entities.size())]; // generates a random position in the map using entites so that pacman can move without bugs
}
void CherryPowerUp::activate(){
    Entity* Position = getRandomEntity();
    this->getPacman()->setX(Position->getX()); // Uses the random position to move pacman.
    this->getPacman()->setY(Position->getY());
}



