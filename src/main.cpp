#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif

#ifndef _GAME
#define _GAME
#include "Game.h"
#endif
#ifndef STD
#define STD
#include <iostream>
#endif
int main(){
	Game game(800, 600, 144);
	game.initGame("Samuli Survivors");
	game.closeGame();
	return 0;
}
