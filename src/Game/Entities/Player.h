#pragma once

#include "Animation.h"
#include "EntityManager.h"
#include "PowerUp.h"
#include <vector>








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
        vector<PowerUp*> PowerCollection;
        PowerUp* prueba;
        vector<vector<int>>mapMatrix;
            


    public:
        Player(int, int, int , int, EntityManager*, string);
        ~Player();
        int getHealth();
        int getScore();
        EntityManager* getPlayerEm();
        FACING getFacing();
        vector<PowerUp*> getPowerCollection();
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
        void sortPowerUp();
        int StrawStepCounter = 50;
        void lockFruitOnMap();
        Entity* TargetFruit;
        vector <double> fruitDistance;
        vector<vector<int>> PathFinder(int, int,vector<vector<int>>);
        vector<vector<int>> Path;
        int row;
        int col;
        vector<Entity*> fruitVector;
        Entity* findClosestFruit();
        int d = 100000;
        bool drawMatrixFlag = false;
        void createMatrix();
        void drawMatrix();
};