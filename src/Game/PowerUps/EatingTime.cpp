#include"EatingTime.h"

void EatingTime::activate(){
    this->getPacman()->getPlayerEm()->setKillable(true);
}
