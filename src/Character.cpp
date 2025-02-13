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
