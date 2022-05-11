#include"ofMain.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
#include "math.h"
class GPS{
    private:
        vector<vector<int>>mapMatrix;
        Player* player;
        EntityManager* em;
    public:
        GPS(EntityManager* em, Player* player);
        bool drawMatrixFlag = false;
        void createMatrix();
        void drawMatrix();
        void keyPressed(int key);
        void tick();
        void render();
        void lockFruitOnMap(EntityManager*);
        Entity* TargetFruit;
        vector <double> fruitDistance;
        double d;
        vector<vector<int>> PathFinder(int, int,vector<vector<int>>);
        vector<vector<int>> Path;
        int row;
        int col;
};