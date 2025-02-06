#include "Game.h"
#include "Character.h"


#ifndef _VECTOR
#define _VECTOR
#include <vector>
#endif

#ifndef _CHARACTER
#define _CHARACTER
#include "Character.h"
#endif

#include "Nappi.h"

// Create buttons		//TODO: Tehdään joku menu luokka tai joku semmonen johna tehdään napit.
Nappi startButton(200, 150, 150, 50, "start", GREEN);
Nappi exitButton(200, 250, 150, 50, "exit", RED);
Nappi resizeButton(200, 350, 150, 50, "resize", BLUE);

//At this point, only initializes window and OpenGL context, but this function will expand
void Game::initGame(const char* windowName){
	InitWindow(this->screenWidth, this->screenHeight, windowName);
	soundManager.loadSound("background", "assets/sounds/bg.mp3"); // Load background sound
    soundManager.playSound("background"); // Play background sound
	startMainLoop();

}

//Game main loop is here
void Game::startMainLoop(){
	Character testi = Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png", &this->textureManager);
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

	// Draw buttons
	startButton.draw();
	exitButton.draw();
	resizeButton.draw();

	DrawText("Hello World", this->screenWidth / 2, this->screenHeight / 2, 20, BLACK);

	for(Character& c : this->characters){
		//c.drawCharacter(&this->textureManager);
		c.drawCharacter();
	}	
	EndDrawing();
}

//Put everything you want to do before the game closes here
//(If you use memory, you should free it here, if nowhere else)
void Game::closeGame(){
	this->textureManager.unloadAllTextures();
	this->characters.clear();
	soundManager.unloadAllSounds();
	CloseWindow();
}
//Empty for now, but updates should be done (or called), from this function.
void Game::updateGame(){
	this->characters.front().moveCharacter(-1.0f, 0.0f);
	if (startButton.isClicked()) 
	{
		//xdd startGame();
	}
	if (exitButton.isClicked()) 
	{
		closeGame();
	}
	if (resizeButton.isClicked())
 	{
        // see what display we are on right now
 		int display = GetCurrentMonitor();
        
    if (IsWindowFullscreen())
    {
        SetWindowSize(screenWidth, screenHeight);
    }
    else
    {
		SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
	}
 		ToggleFullscreen();
 	}

}
void Game::addCharacter(Character& character){
	this->characters.push_back(character);
}
void Game::addCharacter(float posX, float posY, const char* fileName){
	this->characters.push_back((Character){posX, posY, fileName, &this->textureManager});
}
