#include "Projectile.h"
#include "raymath.h"
#include <iostream>

//returns 1 if the object should be destroyed
int Projectile::update(){
	if(this->timeAlive >= 0){
		this->position = Vector2MoveTowards(this->position, this->direction, this->speed);	
		timeAlive = timeAlive - GetFrameTime();
	}else{
		//this->~Projectile();
		return 1;
		std::cout << "MORO\n";
	}
	return 0;
}
void Projectile::draw(){
	DrawCircle(this->position.x, this->position.y, this->width, PINK);
}
