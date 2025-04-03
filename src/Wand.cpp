#include "Wand.h"

void Wand::shoot(const Vector2& direction){
	this->projectiles.push_back(Projectile(*this->playerPos, direction, 10.0f, 0.5f, 5.0f));	
}
void Wand::update(){
	if(this->shootTimer <= 0){
		shoot((Vector2){0,0});	
		shootTimer = firerate;
	}
	else{
		shootTimer -= GetFrameTime();
	}
	for(Projectile& proj : this->projectiles){
		if(proj.update()){
			this->projectiles.pop_back();
		}
	}
}
void Wand::draw(){
	//TODO: Hoida tämä kuntoon
	for(Projectile& proj : this->projectiles){
		proj.draw();
	}
}
