#include "CharacterState.h"

CharacterState::CharacterState() {
	PacManButton = new Button(ofGetWidth()/6-32, 5*ofGetHeight()/6, 64, 50, "Pac-Man");
    MissPacManButton = new Button(5*ofGetWidth()/6-60, 5*ofGetHeight()/6, 120, 50, "Miss Pac-Man");
	img1.load("images/intro.png");
    PacManSprite.load("images/pacman.png");
	vector<ofImage> leftAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(PacManSprite, i*16, 0, 16, 16);
        leftAnimframes.push_back(temp);
    }
	PacManAnim = new Animation(10,leftAnimframes);

    MissPacManSprite.load("images/misspacman.jpg");
	vector<ofImage> rightAnimframes;
    ofImage temp2;
	for(int i=0; i<3; i++){
        temp2.cropFrom(MissPacManSprite, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp2);
    }
	MissPacManAnim = new Animation(10,rightAnimframes);
}
void CharacterState::tick() {
	PacManButton->tick();
	if(PacManButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
        isPacMan = true;
    }
    MissPacManButton->tick();
	if(MissPacManButton->wasPressed()){
		setNextState("Game");
		setFinished(true);
        isPacMan = false;
	}
    PacManAnim->tick();
    MissPacManAnim->tick();
}
void CharacterState::render() {
	string title = "Pacman Project";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
    PacManAnim->getCurrentFrame().draw(ofGetWidth()/6-50, 5*ofGetHeight()/6-100, 100, 100);
    MissPacManAnim->getCurrentFrame().draw(5*ofGetWidth()/6-50, 5*ofGetHeight()/6-100, 100, 100);
    img1.draw(ofGetWidth()/2 - 250, ofGetHeight()/2 -250, 500,500);
	PacManButton->render();
    MissPacManButton->render();
}

void CharacterState::keyPressed(int key){
	
}

void CharacterState::mousePressed(int x, int y, int button){
	PacManButton->mousePressed(x, y);
    MissPacManButton->mousePressed(x, y);
}

void CharacterState::reset(){
	setFinished(false);
	setNextState("");
	PacManButton->reset();
    MissPacManButton->reset();
}

bool CharacterState::PacMan(){
    return isPacMan;
}

CharacterState::~CharacterState(){
	delete PacManButton;
    delete MissPacManButton;
    delete PacManAnim;
    delete MissPacManAnim;
}