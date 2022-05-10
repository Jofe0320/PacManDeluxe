#pragma once

#include "EntityManager.h"
#include "Animation.h"

class Ghost: public Entity{
    public:
        Ghost(int, int, int, int, ofImage, EntityManager*, string);
        ~Ghost();
        void tick();
        void render();
        bool getKillable();
        void setKillable(bool);
        void setEyes();
        bool eyes = false;
    private:
        bool killable = false;
        string ghostSpawn;
        FACING facing = UP;
        bool canMove = true;
        bool justSpawned=true;
        void checkCollisions();
        int speed=2;
        vector <int> xPosition;
        vector <int> yPosition;
        EntityManager* em;
        Animation* killableAnim;

};