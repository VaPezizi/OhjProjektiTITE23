#ifndef _GAME
#define _GAME
#include "Game.h"
#endif

//At this point, only initializes window and OpenGL context, but this function will expand
void Game::initGame(const char* windowName){
	InitWindow(this->screenWidth, this->screenHeight, windowName);
	startMainLoop();

}

//Game main loop is here
void Game::startMainLoop(){
	while(!WindowShouldClose()){	
		//Updating game logic 
		this->updateGame();	
		
		//Drawing the game	
		this->drawGame();
	}
	this->closeGame();
}

//All drawing should be done in this function
void Game::drawGame(){

	//Starts Draw mode, all draw calls should be made here (if possible)
	//We can draw in other places if needed, but opening draw mode has to be done there then.

	BeginDrawing();

	ClearBackground(WHITE);
	DrawText("Hello World", this->screenWidth / 2, this->screenHeight / 2, 20, BLACK);

	EndDrawing();
}

//Put everything you want to do before the game closes here
//(If you use memory, you should free it here, if nowhere else)
void Game::closeGame(){
	CloseWindow();
}
//Empty for now, but updates should be done (or called), from this function.
void Game::updateGame(){
		
}
