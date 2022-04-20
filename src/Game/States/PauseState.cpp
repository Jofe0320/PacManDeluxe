#include "PauseState.h"

PauseState::PauseState() {
	//button to press to continue playing
	startButton = new Button(ofGetWidth()/2-60, ofGetHeight()/2, 120, 50, "Continue Game");
	img1.load("images/pacman.png");
	vector<ofImage> rightAnimframes;
    ofImage temp;
	for(int i=0; i<3; i++){
        temp.cropFrom(img1, i*16, 0, 16, 16);
        rightAnimframes.push_back(temp);
    }
	anim = new Animation(10,rightAnimframes);

}
void PauseState::tick() {
	startButton->tick();
	anim->tick();
	if(startButton->wasPressed()){
		//Continue state is to continue
		setNextState("Continue");
		setFinished(false);

	}
}
void PauseState::render() {
	string title = "Pacman Project";
	ofDrawBitmapString(title, ofGetWidth()/2-4*title.size(), ofGetHeight()/2-300, 50);
	ofSetBackgroundColor(0, 0, 0);
	ofSetColor(256, 256, 256);
	anim->getCurrentFrame().draw(ofGetWidth()/2-50, ofGetHeight()/2-100, 100, 100);
	startButton->render();


}

void PauseState::keyPressed(int key){
	
}

void PauseState::mousePressed(int x, int y, int button){
	startButton->mousePressed(x, y);
}

void PauseState::reset(){
	setFinished(false);
	setNextState("");
	startButton->reset();
}

PauseState::~PauseState(){
	delete startButton;
	delete anim;
}