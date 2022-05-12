#include"ofMain.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
#include "math.h"
#include "Dot.h"
#include "BigDot.h"
class GPS{
    private:
        vector<vector<int>>mapMatrix;
        Player* player;
        EntityManager* em;
    public:
        GPS(EntityManager* em);
        bool drawMatrixFlag = false;
        void createMatrix();
        void drawMatrix();
        void keyPressed(int key);
        void tick();
        void render();
        void lockFruitOnMap();
        Entity* TargetFruit;
        vector <double> fruitDistance;
        vector<vector<int>> PathFinder(int, int,vector<vector<int>>);
        vector<vector<int>> Path;
        int row;
        int col;
        Player* getPlayer();
        vector<Entity*> fruitVector;
        Entity* findClosestFruit();
        int d = 100000;
};