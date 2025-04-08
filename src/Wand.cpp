#include "Wand.h"
#include <deque>
#include <memory>

void Wand::shoot(const Vector2& direction){
	if(shootTimer <= 0){
		this->projectiles.push_back(Projectile(*this->playerPos, direction, 10.0f, 0.5f, 5.0f));	
		shootTimer = this->firerate;
	}
}
void Wand::update(std::deque<std::shared_ptr<Character>>*characters){
	shootTimer -= GetFrameTime();
	
		
	for(auto it = projectiles.begin(); it != projectiles.end();){
		if((*it).update(characters)){
			it = projectiles.erase(it);
		}else{
			++it;
		}
	}

	/*for(Projectile& proj : this->projectiles){
		if(proj.update()){
			this->projectiles.pop_back();
		}
	}*/
}
void Wand::draw(){
	//TODO: Hoida tämä kuntoon
	for(Projectile& proj : this->projectiles){
		proj.draw();
	}
}
