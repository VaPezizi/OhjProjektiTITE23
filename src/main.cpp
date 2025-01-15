#include <raylib.h>
#include "Game.h"

int main(){
	InitWindow(screenWidth, screenHeight, "Testi");	
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		BeginDrawing();

		ClearBackground(WHITE);
		DrawText("Hello World!", screenWidth / 2, screenHeight / 2, 20, BLACK);

		EndDrawing();
	}
	return 0;
}
