#ifndef _RAYLIB
#include <raylib.h> 
#define _RAYLIB
#endif
#pragma once

#ifndef _VECTOR
#define _VECTOR
#include <vector>
#endif

#include "Character.h"
#include "SoundManager.h"
#include "TextureManager.h"
//#include "Menu.h"
#include "Scene.h"
//#include "Player.h"
#ifndef _GAME
#define _GAME

class Game{
protected:
	int screenWidth = 800;	
	int screenHeight = 600;

	int windowPosX = 100; // Window position X
	int windowPosY = 100; // Window position Y

	Vector2 mousePos; 

	bool fullScreen = 0; 
	
	/*
	Menu menu;
	std::vector<Character> characters;
	*/

	std::vector<Scene> scenes;
	bool isGameRunning = false; 

	double lastResizeTime = 0; // Last resize time

	
private:
	int currentScene;
	SoundManager soundManager;
	TextureManager textureManager;
	void resetToMainMenu(); // Reset to main menu

public: 
	Game(const int& screenWidth, const int& screenHeight, const int& FPS){
		//this->pelaaja = Player((float)screenWidth / 2, (float)screenHeight / 2, "assets/testTexture.png", &this->textureManager);
		currentScene = 0;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		SetTargetFPS(FPS);
		this->scenes = std::vector<Scene>();
		this->mousePos = (Vector2){0,0};


	}
	void updateButtonPositions();

	Vector2& getScreenDimensions();
	void initGame(const char* windowName);	//Inits the game, with a given name
	void closeGame();		//Closes the game, this is where frees should be called from, if nowhere else
	void startMainLoop();		//Runs the main loop
	void makeMainMenu();
	void drawGame();		//Most draw calls should be made / called from here
	void updateGame();		//Game updates should be made / called from here
	//void addCharacter(Character& character);
	void addPlayer(float posX, float posY, const char* fileName);
	void addCharacter(float posX, float posY, const char* fileName);
	void toggleFullScreen(); // Toggle fullscreen
	
	void makeMenu2();
	
};
#endif
