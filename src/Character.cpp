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

void Character::updateExperience() {
    static double lastXpIncreaseTime = 0;
    double currentTime = GetTime();

    if (IsKeyPressed(KEY_E) && currentTime - lastXpIncreaseTime >= 0.5) {
        lastXpIncreaseTime = currentTime;
        experiencePoints += 20;

        if (experiencePoints >= xpThreshold) {
            experiencePoints -= xpThreshold;
            level++;
            xpThreshold += 50;
        }
    }
}

void Character::resetStats() {
    experiencePoints = 0;
    level = 1;
    xpThreshold = 100;
}

