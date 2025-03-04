#include "Character.h"
#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif

void Character::drawCharacter(){
	this->textures->drawTexture(this->texture, this->position.x, this->position.y);
	//DrawTexture(textures->getTexture(this->texture), this->position.x, this->position.y, WHITE);
}
void Character::moveCharacter(float x, float y){
	this->position.x += x;
	this->position.y += y;
	
}

void Character::updateCharacter(){
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) moveCharacter(0, -1);
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) moveCharacter(0, 1);
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) moveCharacter(-1, 0);
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) moveCharacter(1, 0);
}
