#include "GameState.h"
#include "Entity.h"
#include "EntityManager.h"

GameState::GameState() {
	music.load("music/pacman_chomp.wav");
	mapImage.load("images/map1.png");
	map = MapBuilder().createMap(mapImage);
}
void GameState::tick() {
	if(!music.isPlaying()){
			music.play();
	}
	map->tick();
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
	map = MapBuilder().createMap(mapImage);
}

int GameState::getFinalScore(){
	return finalScore;
}

int GameState::getCurrentScore(){
	return CurrentScore;
}

GameState::~GameState(){
	delete map;
}