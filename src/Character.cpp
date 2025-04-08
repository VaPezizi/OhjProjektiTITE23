#include "Character.h"
#include <deque>
#include <memory>
#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif

void Character::drawCharacter(){
	this->textures->drawTexture(this->texture, this->position.x, this->position.y);
	//DrawRectangle(bbox.x, bbox.y, bbox.width, bbox.height, PINK);
	DrawTexture(textures->getTexture(this->texture), this->position.x, this->position.y, WHITE);
}
void Character::moveCharacter(float x, float y){
	this->position.x += x;
	this->position.y += y;
	
}
Rectangle& Character::getBbox(){
	return this->bbox;
}
//TODO: Tee tänne toiminnallisuutta pelin tekemisen edetessä
void Character::updateCharacter(std::deque<std::shared_ptr<Character>>*characters){
	this->bbox.x = this->position.x;
	this->bbox.y = this->position.y;
	/*float speed = 1.0f;
	bool movingHorizontally = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
	bool movingVertically = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

	if (movingHorizontally && movingVertically) {
	speed *= 0.7f;
	}

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) moveCharacter(0, -speed);
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) moveCharacter(0, speed);
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) moveCharacter(-speed, 0);
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) moveCharacter(speed, 0);
	*/
}
void Character::kill(){
	this->shouldBeKilled = 1;
}
bool Character::getKilled(){
	return this->shouldBeKilled;
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

