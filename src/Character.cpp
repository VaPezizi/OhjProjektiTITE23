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
    float speed = 1.0f;
    bool movingHorizontally = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
    bool movingVertically = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

    if (movingHorizontally && movingVertically) {
        speed *= 0.7f;
    }

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) moveCharacter(0, -speed);
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) moveCharacter(0, speed);
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) moveCharacter(-speed, 0);
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) moveCharacter(speed, 0);
}
