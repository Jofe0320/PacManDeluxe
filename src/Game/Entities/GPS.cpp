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
        for (int x = 207;x<815;x+=16){
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
    int y = 100;
    for (int i = 0; i<mapMatrix.size();i++){
        int x = 50;
        for (int j = 0;j<mapMatrix[i].size();j++){
            if(mapMatrix[i][j] == 1) ofSetColor(0,0,255);
            if(mapMatrix[i][j] == 2) ofSetColor(255,0,0);
            if(mapMatrix[i][j] == 3) ofSetColor(255,255,0);
            if(mapMatrix[i][j] == 0) ofSetColor(0,255,0);
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
    }
}

void GPS::lockFruitOnMap(){
    for (auto x : em->entities){
        if (dynamic_cast<Cherry*>(x)){
            TargetFruit = x;
            mapMatrix[(TargetFruit->getY()-64)/16][(TargetFruit->getX()-200)/16] = 2;
            break;
        }
        if (dynamic_cast<Fruits*>(x)){
            TargetFruit = x;
            mapMatrix[(TargetFruit->getY()-64)/16][(TargetFruit->getX()-200)/16] = 2;
            break;
        }
        if (dynamic_cast<GhostKiller*>(x)){
            TargetFruit = x;
            mapMatrix[(TargetFruit->getY()-64)/16][(TargetFruit->getX()-200)/16] = 2;
            break;
        }
        if (dynamic_cast<Strawberry*>(x)){
            TargetFruit = x;
            mapMatrix[(TargetFruit->getY()-64)/16][(TargetFruit->getX()-200)/16] = 2;
            break;
        }
        if (dynamic_cast<Ultimate*>(x)){
            TargetFruit = x;
            mapMatrix[(TargetFruit->getY()-64)/16][(TargetFruit->getX()-200)/16] = 2;
            break;
        }
    }
    
}
