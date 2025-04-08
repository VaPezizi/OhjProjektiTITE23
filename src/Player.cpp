#include "Player.h"
#include <deque>
#include <memory>
#include <vector>

void Player::updateCharacter(std::deque<std::shared_ptr<Character>>*characters){
	
	float speed = 1.0f;
	bool movingHorizontally = IsKeyDown(KEY_A) ||  IsKeyDown(KEY_D);
	bool movingVertically = IsKeyDown(KEY_W) || IsKeyDown(KEY_S);

	if (movingHorizontally && movingVertically) {
		speed *= 0.7f;
	}
	if (IsKeyDown(KEY_W)) 
		moveCharacter(0, -speed);
	if (IsKeyDown(KEY_S)) 
		moveCharacter(0, speed);
	if (IsKeyDown(KEY_A)) 
		moveCharacter(-speed, 0);
	if (IsKeyDown(KEY_D)) 
		moveCharacter(speed, 0);

	
	if(IsKeyDown(KEY_UP))
		weapons[0]->shoot((Vector2){0, 1});
	if(IsKeyDown(KEY_DOWN))
		weapons[0]->shoot((Vector2){0, -1});
	if(IsKeyDown(KEY_RIGHT))
		weapons[0]->shoot((Vector2){-1, 0});
	if(IsKeyDown(KEY_LEFT))
		weapons[0]->shoot((Vector2){1, 0});


	for(std::shared_ptr<Weapon> weapon : this->weapons)
		weapon->update(characters);

	Character::updateCharacter(characters);
}
Vector2 Player::getPosition(){
	return this->position;
}/*
void Player::addWeapon(const Weapon& weapon){
	this->weapons.push_back(weapon);
}
const std::vector<Weapon>& Player::getWeapons(){
	return this->weapons;
}*/
void Player::drawCharacter(){
	for(std::shared_ptr<Weapon>& weapon : this->weapons){
		weapon->draw();
	}
	Character::drawCharacter();
}
const int& Player::getInventorySpace(){
	return this->inventorySpace;
}
Player::~Player(){}
