#include "UltimatePowerUp.h"
// Give Pacman a point boost
Player* UltimatePowerUp::getPacman(){
    return this->Pacman;
}
void UltimatePowerUp::activate(){
    this->getPacman()->sortPowerUp();
}