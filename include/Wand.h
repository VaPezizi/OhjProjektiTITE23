#ifndef _WAND
#define _WAND
#include <string>
#include <vector>
#include "Weapon.h"
#include "raylib.h"
#include "Projectile.h"

class Wand : public Weapon{
private:
	std::vector<Projectile>projectiles;
public:
	Wand(float damage, float range, float firerate, Vector2* playerPos): Weapon(damage, range, firerate, playerPos){
		this->projectiles = std::vector<Projectile>();
		this->projectiles.reserve(100);
	}
	virtual void shoot(const Vector2& direction);
	virtual void update();
	virtual void draw();
	virtual ~Wand(){
		this->projectiles.clear();	
	}
};
#endif
