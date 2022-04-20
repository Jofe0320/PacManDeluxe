#include"EatingTime.h"
//Debugger Power Up
Player* EatingTime::getPacman(){
    return this->Pacman;
}

void EatingTime::activate(){
    this->getPacman()->getPlayerEm()->setKillable(true);
}

