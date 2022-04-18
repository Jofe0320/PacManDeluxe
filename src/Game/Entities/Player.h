#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "PowerUp.h"








enum MOVING {
	MUP,
	MDOWN,
	MLEFT,
	MRIGHT,
};
class Player: public Entity{

    private:
        int spawnX, spawnY;
        unsigned int health=3;
        int score=0;
        int fruitScore = rand()%41+10;
        bool canMoveUp, canMoveDown, canMoveRight, canMoveLeft;
        int speed = 4;
        bool walking = false;
        MOVING moving;
        FACING facing = DOWN;
        ofImage up, down, left, right;
        Animation *walkUp;
        Animation *walkDown;
        Animation *walkLeft;
        Animation *walkRight;
        EntityManager* em;
        PowerUp* Power;
            


    public:
        Player(int, int, int , int, EntityManager*, string);
        ~Player();
        int getHealth();
        int getScore();
        EntityManager* getPlayerEm();
        FACING getFacing();
        void setHealth(int);
        void setScore(int);
        void setFacing(FACING facing);
        void tick();
        void render();
        void keyPressed(int);
        void keyReleased(int);
        void damage(Entity* damageSource);
        void mousePressed(int, int, int);
        void reset();
        void checkCollisions();
        void die();
        bool CherryFlag = false;
        bool straw = false;
        bool fruit = false;
        int StrawStepCounter = 50;
};