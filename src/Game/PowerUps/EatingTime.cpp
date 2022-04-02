#include"EatingTime.h"

Player* EatingTime::getPacman(){
    return this->Pacman;
}

void EatingTime::activate(){
    this->getPacman()->getPlayerEm()->setKillable(true);
}

