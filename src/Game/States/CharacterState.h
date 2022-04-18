#pragma once

#include "State.h"
#include "Button.h"
#include "Animation.h" 

class CharacterState : public State {
private:
	ofImage img1;
    ofImage PacManSprite;
    ofImage MissPacManSprite;
	Button *PacManButton;
    Button *MissPacManButton;
    Animation* PacManAnim;
    Animation* MissPacManAnim;

public:
	CharacterState();
	~CharacterState();
	void tick();
	void render();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void reset();
    bool isPacMan;
    bool PacMan();
};
