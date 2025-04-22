#include "Wand.h"
#include "Game.h"
#include <deque>
#include <memory>


void Wand::shoot(const Vector2& direction){
	if(shootTimer <= 0){
		this->projectiles.push_back(Projectile(*this->playerPos, direction, 5.0f, 0.5f, 5.0f));	
		shootTimer = this->firerate;
	}
}
void Wand::update(std::deque<std::shared_ptr<Character>>* characters) {
    shootTimer -= GetFrameTime();

    for (auto it = projectiles.begin(); it != projectiles.end(); ) {
		int result = it->update(characters);

        if (result == 2 && game) {
            game->addXP(20); // XP:tä vain jos oikeasti osui viholliseen TODO: ei toimi
            it = projectiles.erase(it);
        } else if (result == 1) {
            it = projectiles.erase(it); // Poistetaan vain vanhentunut ammus
        } else {
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
