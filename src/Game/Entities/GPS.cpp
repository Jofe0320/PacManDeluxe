#include"GPS.h"
#include"Strawberry.h"
#include"Fruits.h"
#include"GhostKiller.h"
#include"Cherry.h"
#include"Ultimate.h"
GPS::GPS(EntityManager* em,Player* player){
    this->em = em;
    this->player = player;
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
<<<<<<< HEAD
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
<<<<<<< HEAD
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
    mapMatrix[13][15] = 2;
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
            lockFruitOnMap(em);
            break;
        case '5':
            Path = PathFinder(37,1,Path);
            break;
    }
}

<<<<<<< HEAD
void GPS::lockFruitOnMap(EntityManager* em){
    for (Entity* x : em->entities){
        if (dynamic_cast<Cherry*>(x) || dynamic_cast<Fruits*>(x)|| dynamic_cast<GhostKiller*>(x)||dynamic_cast<Strawberry*>(x)||dynamic_cast<Ultimate*>(x)){
            d=sqrt((pow((x->getX()-player->getX()),2))+(pow((x->getY()-player->getY()),2)));
                fruitDistance.push_back(d);
        }
    }
    double lowest = fruitDistance[0];
    int j =0;
    for (int i =1; i<fruitDistance.size(); i++){
        if(lowest > fruitDistance[i]){
            lowest = fruitDistance[i];
            j=i;
        }
    }

int k = -1;
    for (Entity* x : em->entities){
        if (dynamic_cast<Cherry*>(x) || dynamic_cast<Fruits*>(x)|| dynamic_cast<GhostKiller*>(x)||dynamic_cast<Strawberry*>(x)||dynamic_cast<Ultimate*>(x)){
        k++;
        if(k == j){
            mapMatrix[(x->getY()-64)/16][(x->getX()-200)/16] = 2;
            break;
        }
        }
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