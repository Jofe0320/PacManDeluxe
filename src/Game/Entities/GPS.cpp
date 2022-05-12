#include"GPS.h"
#include"Strawberry.h"
#include"Fruits.h"
#include"GhostKiller.h"
#include"Cherry.h"
#include"Ultimate.h"
GPS::GPS(EntityManager* em){
    this->em = em;
    createMatrix();

}

void GPS::render(){
    if(drawMatrixFlag == true){
        drawMatrix();
    }
}

//Change code as much as posible 
void GPS::createMatrix(){
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
//Change code as much as POsible 
void GPS::drawMatrix(){
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
            else if(mapMatrix[i][j] == 6) ofSetColor(255,255,255);
            ofDrawBitmapString(ofToString(mapMatrix[i][j]),x,y);
            x += 16;
        }
        y += 16;
    }
}

void GPS::keyPressed(int key){
    switch (key){
        case '2':
            if (drawMatrixFlag == false){
                drawMatrixFlag = true;
            }else{
                drawMatrixFlag = false;
            }
            break;
        case '3':
            lockFruitOnMap();
            break;
        case '5':
            PathFinder(row, col, Path);
            break;
    }
}

Player* GPS::getPlayer(){
    return this->player;
}

Entity* GPS::findClosestFruit(){
    for(Entity* entity: em->entities){
        if (!dynamic_cast<Dot*>(entity) && !dynamic_cast<BigDot*>(entity) && !dynamic_cast<Player*>(entity)){
            fruitVector.push_back(entity);
    }
    }

    for(Entity* entity: fruitVector){
        if(d > sqrt((pow((entity->getX()-getPlayer()->getX()),2))+(pow((entity->getY()-getPlayer()->getY()),2)))){
            d = sqrt(pow((entity->getX()-getPlayer()->getX()),2))+(pow((entity->getY()-getPlayer()->getY()),2));
            TargetFruit = entity;
        }
        }
    return TargetFruit;
}

void GPS::lockFruitOnMap(){
    mapMatrix[(findClosestFruit()->getY()-64)/16][(findClosestFruit()->getX()-200)/16] = 2;
}

vector<vector<int>> GPS::PathFinder(int row, int col,vector<vector<int>>Path){
    
    if (row < 0 || row > 39) {
        return Path;
    }
    if (col < 0 || col > 39) {
        
        return Path;
    }
    if (mapMatrix[row][col] == 2) {  // Found Power
        vector<int> x = {row,col};
        Path.push_back(x);
        return Path;
    }
    if (mapMatrix[row][col] == 1) {  // Hit on wall
        return Path;
    }
    if (mapMatrix[row][col] == 3) {  // Been there
        return Path;
    }
    mapMatrix[row][col] = 3;  // Mark new place

    Path = PathFinder(row-1, col,Path);
    if (!Path.empty()) {  // Try up
        vector<int> x = {row,col};
        Path.push_back(x);
        return Path;
    }
    Path = PathFinder(row, col+1,Path);
    if (!Path.empty()) {  // Try right
        vector<int> x = {row,col};
        Path.push_back(x);
        return Path;
    }
    Path = PathFinder(row+1, col,Path);
    if (!Path.empty()) {  // Try Down
        vector<int> x = {row,col};
        Path.push_back(x);
        return Path;
    }
    Path = PathFinder(row, col-1,Path);
    if (!Path.empty()) {  // Try left
        vector<int> x = {row,col};
        Path.push_back(x);
        return Path;
    }
    return Path;

}