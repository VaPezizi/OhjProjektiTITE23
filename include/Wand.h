#ifndef _WAND
#define _WAND
#include <string>
#include <vector>
#include <deque>
#include "Weapon.h"
#include "raylib.h"
#include "Projectile.h"

class Wand : public Weapon{
private:
	std::deque<Projectile>projectiles;
public:
	Wand(float damage, float range, float firerate, Vector2* playerPos): Weapon(damage, range, firerate, playerPos){
		this->projectiles = std::deque<Projectile>();
	}
	virtual void shoot(const Vector2& direction);
	virtual void update(std::deque<std::shared_ptr<Character>>* characters);
	virtual void draw();
	virtual ~Wand(){
		this->projectiles.clear();	
	}
};
#endif
