#pragma once

#include "ofMain.h" 
#include "Map.h"
#include "Dot.h"
#include "BigDot.h"
#include "Ghost.h"
#include "Cherry.h"
#include "Strawberry.h"
#include "CharacterState.h"
#include "Fruits.h"
#include "GhostKiller.h"

class MapBuilder {
    public:
        MapBuilder();
	    Map* createMap(ofImage, string);

	private:
        vector<ofImage> bound;
        int pixelMultiplier;
        ofColor boundBoundBlock;
        ofColor pacman;
        ofColor ghostC;
	    ofColor dotC;
	    ofColor bigDotC;
        ofImage pacmanSpriteSheet;
        vector <ofImage>* fruits;
        ofImage tempBound;
        ofImage getSprite(ofImage, int, int);
        EntityManager* entityManager;
        CharacterState* characterID;
        int dotCounter = 0;
        int keyNumber =1;
};