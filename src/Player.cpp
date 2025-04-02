#include "Player.h"
#include <memory>
#include <vector>

void Player::updateCharacter(){
	
	float speed = 1.0f;
	bool movingHorizontally = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);
	bool movingVertically = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);

	if (movingHorizontally && movingVertically) {
		speed *= 0.7f;
	}
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
		moveCharacter(0, -speed);
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
		moveCharacter(0, speed);
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
		moveCharacter(-speed, 0);
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
		moveCharacter(speed, 0);

	for(std::shared_ptr<Weapon> weapon : this->weapons)
		weapon->update();

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
