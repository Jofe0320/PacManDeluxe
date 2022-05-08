#include "GameState.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Ultimate.h"


GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage, getCharacter());
	pacmanSpriteSheet.load("images/Background.png");
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
	if(map->getPlayer()->getScore()>=1000){
		map->addEntity(new Ultimate(map->getEntityManager()->entities[0]->getX(),map->getEntityManager()->entities[0]->getY(),16,16,pacmanSpriteSheet));
	}
	if(map->getPlayer()->getHealth() == 0){
		setFinished(true);
		setNextState("over");
		map->getPlayer()->setHealth(3);
		finalScore = map->getPlayer()->getScore();
		map->getPlayer()->setScore(0);
	}
	else if(map->getEntityManager()->NoDots()){
		setNextState("Win");
		setFinished(false);
		CurrentScore = map->getPlayer()->getScore();
	}
	else if(getNextState() == "ContGame" && map->getPlayer()->getScore() == 0){
		map->getPlayer()->setScore(getCurrentScore());
	}
}	

void GameState::render() {
	string PowerNames = "";
	for (int i = 0; i < map->getPlayer()->getPowerCollection().size();i++){
		if (map->getPlayer()->getPowerCollection().size() == 1){
			PowerNames = PowerNames + map->getPlayer()->getPowerCollection()[i]->getName();
		}else{
		PowerNames = PowerNames + "| " + map->getPlayer()->getPowerCollection()[i]->getName();
		}
	}
	ofDrawBitmapString(PowerNames, ofGetWidth()/2-4*PowerNames.size(), (ofGetHeight()/2-300) + 625, 50);
	map->render();
}

void GameState::keyPressed(int key){
	map->keyPressed(key);
	if(key == 'y'){
		CurrentScore = map->getPlayer()->getScore();
		setNextState("Win");
		}
		else if(key == 'p'){
		setNextState("Pause");
		}
}

void GameState::mousePressed(int x, int y, int button){
	map->mousePressed(x, y, button);
}

void GameState::keyReleased(int key){
	map->keyReleased(key);
}

void GameState::reset(){
	setFinished(false);
	setNextState("");
	map = MapBuilder().createMap(mapImage, getCharacter());
}

int GameState::getFinalScore(){
	return finalScore;
}

int GameState::getCurrentScore(){
	return CurrentScore;
}

string GameState::getCharacter(){
	return CharacterSelected;
}

void GameState::setCharacter(string Character){
	CharacterSelected = Character;
}

GameState::~GameState(){
	delete map;
}