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
#include "UltimatePowerUp.h"
#include "Ultimate.h"


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
    if(drawMatrixFlag == true){
        drawMatrix();
    }
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
        case 'j':
            prueba = new UltimatePowerUp(this);
            prueba->activate();
            break;
        case ' ':
            if (PowerCollection.size()>=1){
            PowerCollection[0]->activate();
            PowerCollection.erase(PowerCollection.begin());
            }
            break; 
        // This Controls everything that has to do with the GPS mode
        case '1':
            if (drawMatrixFlag == false){
                createMatrix();       
                drawMatrixFlag = true;
            }else{
                drawMatrixFlag = false;
                mapMatrix.clear();
            }
            if(target == false){
            target = true;
            lockFruitOnMap();
            }
            else{
                d = 10000;
                fruitVector.clear();
                target = false;
            }
            Path.clear();
            if(target == true){
            row = (getY()-64)/16;
            col = (getX()-200)/16;
            PathFinder(row, col, Path);
            }
        if(target == true){
        for (unsigned int i = 0; i < Path.size()-1; i++){
        mapMatrix[Path[i][0]][Path[i][1]] = 6;
        }
        for (int i = 0; i <=39; i++){
            for (int j = 0; j<40;j++){
                if(!(mapMatrix[i][j] == 1) && !(mapMatrix[i][j] == 6)){
                    mapMatrix[i][j] = 0;
                }
            }
        }
        break;
        }
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
vector<PowerUp*> Player::getPowerCollection(){return PowerCollection;}
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
                PowerCollection.push_back(new CherryPowerUp(this,this->getPlayerEm()));

            }
            if(dynamic_cast<Strawberry*>(entity)){
                score +=20;
                entity->remove = true;
                PowerCollection.push_back(new StrawberryPowerUp(this,this->getPlayerEm()));

            }
            if(dynamic_cast<Fruits*>(entity)){
                entity->remove = true;
                PowerCollection.push_back(new RandomPowerUp(this,this->getPlayerEm()));
                
            }
            if(dynamic_cast<GhostKiller*>(entity)){
                score +=20;
                entity->remove = true;
                PowerCollection.push_back(new GhostKillerPowerUp(this,this->getPlayerEm()));
            }
            if(dynamic_cast<Ultimate*>(entity)){
                prueba = new UltimatePowerUp(this);
                prueba->activate();
                entity->remove = true;
            }
        }
    }
    for(Entity* entity:em->ghosts){
        if(collides(entity)){
            Ghost* ghost = dynamic_cast<Ghost*>(entity);
            if (StrawStepCounter > 50){
            if(ghost->getKillable() && ghost->eyes == false){
                ghost->setKillable(false);
                ghost->eyes = true;
            }
            else if (ghost->getKillable() == false && ghost->eyes == false){
                die();
            }
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
// This method uses selection sort algorithm to sort the powerUps
void Player::sortPowerUp(){
    if(PowerCollection.size()>1){
    for (int i = 0; i < PowerCollection.size()-1;i++){
        int MaxPos = i;
        for (int j = i + 1; j < PowerCollection.size();j++){
            if (PowerCollection[j]->getRank()>PowerCollection[MaxPos]->getRank()){
                MaxPos = j;
            }
        }
        PowerUp* temp = PowerCollection[i];
        PowerCollection[i] = PowerCollection[MaxPos];
        PowerCollection[MaxPos] = temp;
    }
    }
}
// Create the map Matrix (fills the vector int the .h file)
void Player::createMatrix(){
    for (int y = 72; y < 712;y += 16){
        mapMatrix.push_back(vector<int>());
        for (int x = 207;x<816;x+=16){

            bool foundBound = false;
            for (auto w : em->boundBlocks){
                if (ofRectangle(x,y,1,1).intersects(w->getBounds())){
                    mapMatrix[mapMatrix.size()-1].push_back(1);
                    foundBound = true;
                    break;
                }
            }
            if(foundBound == false) mapMatrix[mapMatrix.size()-1].push_back(0);
        }
    }
}

// Draws the map Matrix on the screen
void Player::drawMatrix(){
    int y = 76;
    for (int i = 0; i<mapMatrix.size();i++){
        int x = 204;
        for (int j = 0;j<mapMatrix[i].size();j++){
            if(mapMatrix[i][j] == 1) ofSetColor(0,0,255);
            else if(mapMatrix[i][j] == 2) ofSetColor(255,211,25);
            else if(mapMatrix[i][j] == 3) ofSetColor(255,255,0);
            else if(mapMatrix[i][j] == 0) ofSetColor(0,0,0);
            else if(mapMatrix[i][j] == 4) ofSetColor(0,255,0);
            else if(mapMatrix[i][j] == 5) ofSetColor(255,255,0);
            else if(mapMatrix[i][j] == 6) ofSetColor(255,0,255);
            ofDrawBitmapString(ofToString(mapMatrix[i][j]),x,y);
            x += 16;
        }
        y += 16;
    }
}
// Uses the Formula of Distance to establish what is the closest fruit
Entity* Player::findClosestFruit(){
    for(Entity* entity: getPlayerEm()->entities){
        if (!dynamic_cast<Dot*>(entity) && !dynamic_cast<BigDot*>(entity) && !dynamic_cast<Player*>(entity)){
            fruitVector.push_back(entity);
    }
    }

    for(Entity* entity: fruitVector){
        if(d > sqrt((pow((entity->getX()-x),2))+(pow((entity->getY()-y),2)))){
            d = sqrt(pow((entity->getX()-x),2)+(pow((entity->getY()-y),2)));
            TargetFruit = entity;
        }
        }
    return TargetFruit;
}
// Inserts a value of 2 in the position of the Target Fruit in the map
void Player::lockFruitOnMap(){
    mapMatrix[(findClosestFruit()->getY()-64)/16][(findClosestFruit()->getX()-200)/16] = 2;
}

// Recursive Path Finding algorithm that saves all the coordinates into a vector of vectors of int 
vector<vector<int>> Player::PathFinder(int row, int col,vector<vector<int>> Path){
    
    if (!(row >= 0) && !(row <= 39)){
        return this->Path;
    }
    if (!(col >= 0) && !(col <= 42)){
        
        return this->Path;
    }
    if (mapMatrix[row][col] == 2) {  // Found Power
        vector<int> x = {row,col};
        this->Path.push_back(x);
        return this->Path;
    }
    if (mapMatrix[row][col] == 1) {  // Hit on wall
        return this->Path;
    }
    if (mapMatrix[row][col] == 3) {  // Been there
        return this->Path;
    }
    mapMatrix[row][col] = 3;  // Mark new place
    
    this->Path = PathFinder(row-1, col,Path);
    if (!this->Path.empty()) {  // Try up
        vector<int> x = {row,col};
        this->Path.push_back(x);
        return this->Path;
    }
    this->Path = PathFinder(row, col+1,Path);
    if (!this->Path.empty()) {  // Try right
        vector<int> x = {row,col};
        this->Path.push_back(x);
        return this->Path;
    }
    this->Path = PathFinder(row+1, col,Path);
    if (!this->Path.empty()) {  // Try Down
        vector<int> x = {row,col};
        this->Path.push_back(x);
        return this->Path;
    }
    this->Path = PathFinder(row, col-1,Path);
    if (!this->Path.empty()) {  // Try left
        vector<int> x = {row,col};
        this->Path.push_back(x);
        return this->Path;
    }
    return this->Path;
}