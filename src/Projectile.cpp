#include "Projectile.h"
#include <deque>
#include <memory>
#include "Character.h"

//returns 1 if the object should be destroyed
int Projectile::update(std::deque<std::shared_ptr<Character>>* characters){
	Rectangle bbox = (Rectangle){this->position.x, this->position.y, this->width, this->width};
	if(this->timeAlive >= 0){
		this->position = (Vector2){this->position.x - this->direction.x, this->position.y - this->direction.y};
		//this->position = Vector2MoveTowards(this->position, this->direction, this->speed);	
		timeAlive = timeAlive - GetFrameTime();
	}else{
		//this->~Projectile();
		//this->shouldBeKilled = 1;
		return 1;
	}

	bool isFirst = true;
    for (auto it = characters->begin(); it != characters->end(); ++it) {
        if (isFirst) {
            isFirst = false;
            continue; 
        }

		if (CheckCollisionRecs((*it)->getBbox(), bbox)) {
			(*it)->kill();
			std::cout << "killed enemy :D\n";
			return 2; 
		}		
    }
	/*//Ruma ratkasu, älä kato:DD
	auto it = characters->begin();
	if(it != characters->end())
		++it;
	for(;it != characters->end();){
		if(CheckCollisionRecs((*it)->getBbox(), bbox)){
			(*it)->kill();
			std::cout << "Killed enemy :D\n";
			++it;
			//it = characters->erase(it);
		}else{
			++it;
		}
	}
	/*for(auto& c : *characters){
		if(CheckCollisionRecs(c->getBbox(), bbox)){
			std::cout << "Hell yeah\n";
			c->kill();
			return 1;
		}
	}*/
	return 0;
}
void Projectile::draw(){
	DrawCircle(this->position.x, this->position.y, this->width, PINK);
}
