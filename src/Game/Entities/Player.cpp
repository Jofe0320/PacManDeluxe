#include "Player.h"
#include "EntityManager.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "PowerUp.h"
#include"EatingTime.h"
#include"PowerUp.h"
#include "Cherry.h"
#include"CherryPowerUp.h"
#include"Strawberry.h"
#include"StrawberryPowerUp.h"
#include "Fruits.h"
#include "RandomPowerUp.h"
#include "GhostKiller.h"
#include "GhostKillerPowerUp.h"


Player::Player(int x, int y, int width, int height, EntityManager* em, string characterSelected) : Entity(x, y, width, height){
    spawnX = x;
    spawnY = y;
    sprite.load(characterSelected);
    down.cropFrom(sprite, 0, 48, 16, 16);
    up.cropFrom(sprite, 0, 32, 16, 16);
    left.cropFrom(sprite, 0, 16, 16, 16);
    right.cropFrom(sprite, 0, 0, 16, 16);
    
    vector<ofImage> downAnimframes;
    vector<ofImage> upAnimframes;
    vector<ofImage> leftAnimframes;
    vector<ofImage> rightAnimframes;
    ofImage temp;
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 48, 16, 16);
        downAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 32, 16, 16);
        upAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 16, 16, 16);
        leftAnimframes.push_back(temp);
    }
    for(int i=0; i<3; i++){
        temp.cropFrom(sprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
    walkDown = new Animation(1,downAnimframes);
    walkUp = new Animation(1,upAnimframes);
    walkLeft = new Animation(1,leftAnimframes);
    walkRight = new Animation(1,rightAnimframes);

    this->em = em;

    moving = MLEFT;
    
}
void Player::tick(){

    checkCollisions();

    if (moving == MUP && canMoveUp) 
        facing = UP;
    else if (moving == MDOWN && canMoveDown) 
        facing = DOWN;
    else if (moving == MLEFT && canMoveLeft) 
        facing = LEFT;
    else if (moving == MRIGHT && canMoveRight)
        facing = RIGHT;

    if(facing == UP && canMoveUp){
        y-= speed;
        walkUp->tick();
        StrawStepCounter += 1;
    }else if(facing == DOWN && canMoveDown){
        y+=speed;
        walkDown->tick();
        StrawStepCounter += 1;
    }else if(facing == LEFT && canMoveLeft){
        x-=speed;
        walkLeft->tick();
        StrawStepCounter += 1;
    }else if(facing == RIGHT && canMoveRight){
        x+=speed;
        walkRight->tick();
        StrawStepCounter += 1;
    }
}

void Player::render(){
    ofSetColor(256,256,256);
    // ofDrawRectangle(getBounds());
    if (StrawStepCounter > 50){    // Uses the strawStepCounter to not render pacman for some steps
    if(facing == UP)
        walkUp->getCurrentFrame().draw(x, y, width, height);
    else if(facing == DOWN)
        walkDown->getCurrentFrame().draw(x, y, width, height);
    else if(facing == LEFT)
        walkLeft->getCurrentFrame().draw(x, y, width, height);
    else if(facing == RIGHT)
        walkRight->getCurrentFrame().draw(x, y, width, height);
    }
    ofSetColor(256, 0, 0);
    ofDrawBitmapString("Health: ", ofGetWidth()/2 + 100, 50);

    for(unsigned int i=0; i<health; i++){
        ofDrawCircle(ofGetWidth()/2 + 25*i +200, 50, 10);
    }
    ofDrawBitmapString("Score:"  + to_string(score), ofGetWidth()/2-200, 50);
    
}

void Player::keyPressed(int key){
    switch(key){
        case 'w':
            moving = MUP;
            break;
        case 's':
            moving = MDOWN;
            break;
        case 'a':
            moving = MLEFT;;
            break;
        case 'd':
            moving = MRIGHT;;
            break;
        case 'n':
            die();
            break;
        case 'm':
            if (getHealth()<3){
                health++;
            }
            break;
        case ' ':
            if(CherryFlag == true || straw == true|| fruit == true||GhostK == true){
            if (CherryFlag == true && cherryCounter >0){
                Power = new CherryPowerUp(this,this->getPlayerEm());
                CherryFlag = false;
                cherryCounter--;
                Power->activate();
            }
            if (straw == true && strawCounter>0){
                Power = new StrawberryPowerUp(this,this->getPlayerEm());
                straw = false;
                strawCounter--;
                Power->activate();
            }
            if (fruit == true && fruitCounter>0){
                Power = new RandomPowerUp(this,this->getPlayerEm());
                fruit = false;
                fruitCounter--;
                Power->activate();
            }
            if (GhostK == true && GhostKCounter >0){
                Power = new GhostKillerPowerUp(this,this->getPlayerEm());
                GhostK = false;
                GhostKCounter--;
                Power->activate();
            }
            }
            else{
                Power = new EatingTime(this);
                Power->activate();
            }
            break; 
    }
}

void Player::keyReleased(int key){
    if(key == 'w' || key =='s' || key == 'a' || key == 'd'){
        walking = false;
    }
}
void Player::mousePressed(int x, int y, int button){

}

int Player::getHealth(){ return health; }
int Player::getScore(){ return score; }
EntityManager* Player::getPlayerEm(){return em;}
FACING Player::getFacing(){ return facing; }
void Player::setHealth(int h){ health = h; }
void Player::setFacing(FACING facing){ this->facing = facing; }
void Player::setScore(int h){ score = h; }

void Player::checkCollisions(){
    canMoveUp = true;
    canMoveDown = true;
    canMoveLeft = true;
    canMoveRight = true;

    for(BoundBlock* boundBlock: em->boundBlocks){
        if(this->getBounds(x, y-speed).intersects(boundBlock->getBounds()))
            canMoveUp = false;
        if(this->getBounds(x, y+speed).intersects(boundBlock->getBounds()))
            canMoveDown = false;
        if(this->getBounds(x-speed, y).intersects(boundBlock->getBounds()))
            canMoveLeft = false;
        if(this->getBounds(x+speed, y).intersects(boundBlock->getBounds()))
            canMoveRight = false;
    }
    for(Entity* entity:em->entities){
        if(collides(entity)){
            if(dynamic_cast<Dot*>(entity) || dynamic_cast<BigDot*>(entity)){
                entity->remove = true;
                score += 10;
            }
            if(dynamic_cast<BigDot*>(entity)){
                score +=50;
                em->setKillable(true);
            }
            if(dynamic_cast<Cherry*>(entity)){
                score +=20;
                entity->remove = true;
                CherryFlag = true;
                cherryCounter = 1;
                GhostKCounter = 0;
                fruitCounter = 0;
                strawCounter = 0;

            }
            if(dynamic_cast<Strawberry*>(entity)){
                score +=20;
                entity->remove = true;
                straw = true;
                strawCounter = 1;
                cherryCounter = 0;
                GhostKCounter = 0;
                fruitCounter = 0;

            }
            if(dynamic_cast<Fruits*>(entity)){
                entity->remove = true;
                fruit = true;
                fruitCounter = 1;
                strawCounter = 0;
                cherryCounter = 0;
                GhostKCounter = 0;
            }
            if(dynamic_cast<GhostKiller*>(entity)){
                score +=20;
                entity->remove = true;
                GhostK = true;
                GhostKCounter = 1;
                fruitCounter = 0;
                strawCounter = 0;
                cherryCounter = 0;

            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if (StrawStepCounter > 50){
            if(ghost->getKillable())
                ghost->remove = true;
            else
                die();
            }
        }
    }

    
}

void Player::die(){
    health--;
    x = spawnX;
    y = spawnY;

}

Player::~Player(){
    delete walkUp;
    delete walkDown;
    delete walkLeft;
    delete walkRight;
}