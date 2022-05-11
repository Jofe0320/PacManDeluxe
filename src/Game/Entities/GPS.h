#include"ofMain.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"
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
        void lockFruitOnMap();
        Entity* TargetFruit;
        vector<vector<int>> PathFinder(int row, int col,vector<vector<int>> Path);
        vector<vector<int>> Path;
};