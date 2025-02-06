#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif
#include "Game.h"

#ifndef STD
#define STD
#include <iostream>
#endif
int main(){
	Game game(800, 600, 144);
	game.initGame("Samuli Survivors");
	game.closeGame();
	//std::cout << "MORO";
	//CloseWindow();
	return 0;
}
