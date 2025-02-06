#include "Game.h"
#include "Character.h"


#ifndef _VECTOR
#define _VECTOR
#include <vector>
#endif

//At this point, only initializes window and OpenGL context, but this function will expand
void Game::initGame(const char* windowName){
	InitWindow(this->screenWidth, this->screenHeight, windowName);
	soundManager.loadSound("background", "assets/sounds/bg.mp3"); // Load background sound
    soundManager.playSound("background"); // Play background sound
	startMainLoop();

}

//Game main loop is here
void Game::startMainLoop(){
	Character testi = Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png");
	//addCharacter(Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png"));
	addCharacter(testi);
	//addCharacter(Character(screenWidth / 2, screenHeight / 2, "assets/testTexture.png"));

	while(!WindowShouldClose()){	
		//Updating game logic 
		this->updateGame();	
		
		//Drawing the game	
		this->drawGame();
	}
}

//All drawing should be done in this function
void Game::drawGame(){

	//Starts Draw mode, all draw calls should be made here (if possible)
	//We can draw in other places if needed, but opening draw mode has to be done there then.

	BeginDrawing();

	ClearBackground(WHITE);
	DrawText("Hello World", this->screenWidth / 2, this->screenHeight / 2, 20, BLACK);

	for(Character& c : this->characters){
		c.drawCharacter();
	}	
	EndDrawing();
}

//Put everything you want to do before the game closes here
//(If you use memory, you should free it here, if nowhere else)
void Game::closeGame(){
	this->characters.clear();
	soundManager.unloadAllSounds();
	CloseWindow();
}
//Empty for now, but updates should be done (or called), from this function.
void Game::updateGame(){
	this->characters.front().moveCharacter(-1.0f, 0.0f);
}
void Game::addCharacter(Character& character){
	this->characters.push_back(character);
}
void Game::addCharacter(float posX, float posY, const char* fileName){
	this->characters.push_back((Character){posX, posY, fileName});
}
