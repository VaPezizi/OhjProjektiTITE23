#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif
#include "Game.h"

int main(){
	Game game(800, 600, 144);
	game.initGame("Samuli Survivors");
	return 0;
}
