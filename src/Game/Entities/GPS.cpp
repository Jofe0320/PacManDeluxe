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
        for (int x = 207;x<820;x+=16){
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
            if(mapMatrix[i][j] == 2) ofSetColor(255,0,0);
            if(mapMatrix[i][j] == 3) ofSetColor(255,255,0);
            if(mapMatrix[i][j] == 0) ofSetColor(0,255,0);
            if(mapMatrix[i][j] == 7) ofSetColor(255,0,0);
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
            lockFruitOnMap();
            break;
        case '5':
            Path = PathFinder(37,1,Path);
            break;
    }
}

void GPS::lockFruitOnMap(){
    for (auto x : Path){
        mapMatrix[x[0]][x[1]] = 7;
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