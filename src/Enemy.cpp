#include "Enemy.h"
#include <deque>
#include <memory>
#include <raymath.h>
#include <iostream>

void Enemy::updateCharacter(std::deque<std::shared_ptr<Character>>*characters){

	//Ensiksi lasketaan suunta vihusta pelaajaan
	/*Vector2 moveDirection = Vector2Subtract(player->getPosition(), this->position);
	//Normalisoidaan vektori
	Vector2Normalize(moveDirection);
	Vector2Scale(moveDirection, 0.001f);	
	*/


	Vector2 moveDirection = Vector2MoveTowards(this->position, player->getPosition(), this->speed);
	//std::cout << "X: " << moveDirection.x << "\nY: " << moveDirection.y << std::endl;

	this->position = moveDirection;

	//moveCharacter(moveDirection.x, moveDirection.y);
	Character::updateCharacter(characters);
}
Enemy::~Enemy(){}
