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
#include "Menu.h"

#ifndef _GAME
#define _GAME

class Game{
protected:
	int screenWidth = 800;	
	int screenHeight = 600;

	Vector2 mousePos;

	bool fullScreen = 0;
	
	Menu menu;
	std::vector<Character> characters;
	
private:
	SoundManager soundManager;
	TextureManager textureManager;

public: 
	Game(const int& screenWidth, const int& screenHeight, const int& FPS){
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		SetTargetFPS(FPS);
		this->characters = std::vector<Character>();
		characters.reserve(50);		//Reserving 50 spots for the characters list
		this->mousePos = (Vector2){0,0};
	}

	Vector2& getScreenDimensions();
	void initGame(const char* windowName);	//Inits the game, with a given name
	void closeGame();		//Closes the game, this is where frees should be called from, if nowhere else
	void startMainLoop();		//Runs the main loop
	void drawGame();		//Most draw calls should be made / called from here
	void updateGame();		//Game updates should be made / called from here
	void addCharacter(Character& character);
	void addCharacter(float posX, float posY, const char* fileName);
};
#endif
