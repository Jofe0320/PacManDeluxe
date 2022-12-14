#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetWindowTitle("C++ Game Box");
	//States
	menuState = new MenuState();
	characterState = new CharacterState();
	gameState = new GameState();
	gameOverState = new GameOverState();
	winState = new WinState();
	pauseState = new PauseState();
	// Initial State
	currentState = menuState;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (currentState != nullptr){
		currentState->tick();
		if(currentState->hasFinished()){
			//menu state
			if(currentState->getNextState() == "Menu"){
				currentState = menuState;
			}
			//game State
			else if(currentState->getNextState() == "Game"){
				//chooses Pac-Man or Miss Pac-Man
				if(characterState->PacMan() == true){
					gameState->setCharacter("images/pacman.png");
				}else{gameState->setCharacter("images/misspacman.jpg");}
				currentState = gameState;
			}
			//game over state
			else if(currentState->getNextState() == "over"){
				gameOverState->setScore(gameState->getFinalScore());
				currentState = gameOverState;
			}
			//characterState
			else if (currentState->getNextState() == "Character"){
				currentState = characterState;
			}
			currentState->reset();
		}else if(currentState->hasFinished() == false){
			//winState
			if (currentState->getNextState() =="Win"){
				int tempScore = gameState->getCurrentScore();
				winState->reset();
				winState->setScore(tempScore);
				currentState = winState;
			}
			//game after win
			else if(currentState->getNextState() == "NextGame"){
				currentState = gameState;
				gameState->reset();
				gameState->setNextState("ContGame");
			}
			//pauses game
			else if(currentState->getNextState() == "Pause"){
				pauseState->reset();
				currentState = pauseState;
			}
			//continues after Pause
			else if(currentState->getNextState() == "Continue"){
				currentState = gameState;
				gameState->setNextState("");
		}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (currentState != nullptr)
		currentState->render();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (currentState != nullptr)
		currentState->keyPressed(key);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (currentState != nullptr)
			currentState->keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (currentState != nullptr)
		currentState->mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (currentState != nullptr)
		currentState->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
	if (currentState != nullptr)
			currentState->mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
	if (currentState != nullptr)
		currentState->mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	if (currentState != nullptr)
			currentState->windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	if (currentState != nullptr)
		currentState->gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (currentState != nullptr)
		currentState->dragEvent(dragInfo);
}
