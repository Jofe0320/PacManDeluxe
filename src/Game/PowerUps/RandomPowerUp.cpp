#include "RandomPowerUp.h"
// Give Pacman a point boost
Player* RandomPowerUp::getPacman(){
    return this->Pacman;
}
EntityManager* RandomPowerUp::getEm(){
    return this-> em;
}
Entity* RandomPowerUp::getRandomEntity(){
    return this->getEm()->entities[ofRandom(0,this->getEm()->entities.size())];
}
void RandomPowerUp::activate(){
    Player* Pacman = getPacman();
    Pacman->setScore(Pacman->getScore() + points);
}
