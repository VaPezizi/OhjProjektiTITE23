#include "Enemy.h"
#include <raymath.h>
#include <iostream>

void Enemy::updateCharacter(){

	//Ensiksi lasketaan suunta vihusta pelaajaan
	/*Vector2 moveDirection = Vector2Subtract(player->getPosition(), this->position);
	//Normalisoidaan vektori
	Vector2Normalize(moveDirection);
	Vector2Scale(moveDirection, 0.001f);	
	*/


	Vector2 moveDirection = Vector2MoveTowards(this->position, player->getPosition(), this->speed);
	std::cout << "X: " << moveDirection.x << "\nY: " << moveDirection.y << std::endl;

	this->position = moveDirection;

	//moveCharacter(moveDirection.x, moveDirection.y);
}
Enemy::~Enemy(){}
