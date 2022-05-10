#include "Ghost.h"
#include "BoundBlock.h"

Ghost::Ghost(int x, int y, int width, int height, ofImage spriteSheet, EntityManager* em, string color): Entity(x, y, width, height){
    this->em = em;
    ghostSpawn = color;
    vector<ofImage> killableFrames;
    ofImage temp;
    temp.cropFrom(spriteSheet, 584, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 600, 64, 16, 16);
    killableFrames.push_back(temp);
    temp.cropFrom(spriteSheet, 616, 64, 16, 16);
    killableFrames.push_back(temp);    
    temp.cropFrom(spriteSheet, 632, 64, 16, 16);
    killableFrames.push_back(temp);
    killableAnim = new Animation(10, killableFrames);

    if(color == "red")      sprite.cropFrom(spriteSheet,456,64,16,16);
    else if(color=="pink")  sprite.cropFrom(spriteSheet,456,80,16,16);
    else if(color=="cyan")  sprite.cropFrom(spriteSheet,456,96,16,16);
    else if(color=="orange")sprite.cropFrom(spriteSheet,456,112,16,16);
    

}

void Ghost::tick(){
    killableAnim->tick();
    canMove = true;
    checkCollisions();
    if(canMove && eyes == false){
        if(facing == UP){
            y-= speed;
            yPosition.push_back(y);
            xPosition.push_back(x);
        }else if(facing == DOWN){
            y+=speed;
            yPosition.push_back(y);
            xPosition.push_back(x);
        }else if(facing == LEFT){
            x-=speed;
            yPosition.push_back(y);
            xPosition.push_back(x);
        }else if(facing == RIGHT){
            x+=speed;
            yPosition.push_back(y);
            xPosition.push_back(x);
        }
    }else if(canMove == false && eyes == false){
        int randInt;
        if(justSpawned){
            randInt = ofRandom(2);

        }else{
            randInt = ofRandom(4);
        }
        if(randInt == 0){
            facing = LEFT;
        }else if(randInt == 1){
            facing = RIGHT;
        }else if(randInt == 2){
            facing = DOWN;
        }else if(randInt == 3){
            facing = UP;
        }
        justSpawned = false;

    }else if(eyes == true){
        if(!xPosition.empty() && !yPosition.empty()){
        setEyes();}
        else{
            eyes = false;
            ofImage spriteSheet;
            spriteSheet.load("images/Background.png");
            if(ghostSpawn == "red")      sprite.cropFrom(spriteSheet,456,64,16,16);
            else if(ghostSpawn=="pink")  sprite.cropFrom(spriteSheet,456,80,16,16);
            else if(ghostSpawn=="cyan")  sprite.cropFrom(spriteSheet,456,96,16,16);
            else if(ghostSpawn=="orange")sprite.cropFrom(spriteSheet,456,112,16,16);
            facing = UP;
            justSpawned = true;
            setKillable(false);
            }
    }
}

void Ghost::render(){
    if(killable && eyes == false){
        killableAnim->getCurrentFrame().draw(x,y,width,height);
    }else{
        Entity::render();
    }
}

bool Ghost::getKillable(){
    return killable;
}
void Ghost::setKillable(bool k){
    killable = k;
}
void Ghost::checkCollisions(){
    for(BoundBlock* BoundBlock: em->boundBlocks){
        switch(facing){
            case UP:
                if(this->getBounds(x, y-speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case DOWN:
                if(this->getBounds(x, y+speed).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case LEFT:
                if(this->getBounds(x-speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
            case RIGHT:
                if(this->getBounds(x+speed, y).intersects(BoundBlock->getBounds())){
                    canMove = false;
                }
                break;
        }
    }
}

void Ghost::setEyes(){
    ofImage spriteSheet;
    spriteSheet.load("images/Background.png");
    sprite.cropFrom(spriteSheet, 584, 80, 16, 16);
    if(xPosition[xPosition.size()] == xPosition[xPosition.size()-1]){
    y = y - (yPosition[yPosition.size()] - yPosition[yPosition.size()-1]);
    yPosition.pop_back();
    xPosition.pop_back();
    }
    else if(yPosition[yPosition.size()] == yPosition[yPosition.size()-1])
    {
        x = x - (xPosition[xPosition.size()] - xPosition[xPosition.size()-1]);
        yPosition.pop_back();
        xPosition.pop_back();
    }
    else{
        yPosition.pop_back();
        xPosition.pop_back();
        }
}

Ghost::~Ghost(){
    delete killableAnim;
}