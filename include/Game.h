#ifndef _RAYLIB
#include <raylib.h> 
#define _RAYLIB
#endif
#pragma once


class Game{
protected:
	int screenWidth = 800;	
	int screenHeight = 600;

	Vector2 mousePos;

	bool fullScreen = 0;
public: 
	Game(const int& screenWidth, const int& screenHeight, const int& FPS){
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		SetTargetFPS(FPS);

		this->mousePos = (Vector2){0,0};
	}

	Vector2& getScreenDimensions();
	void initGame(const char* windowName);
	void closeGame();
	void startMainLoop();
	void drawGame();
	void updateGame();
};
