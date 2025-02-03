#ifndef _CHARACTER
#include "Character.h"
#define _CHARACTER
#endif
#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif

void Character::drawCharacter(){
	DrawTexture(this->texture, this->position.x, this->position.y, WHITE);
}
