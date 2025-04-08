#ifndef _WEAPON
#define _WEAPON
#include <deque>
#include <memory>
#include <string>
#include <vector>
#include "raylib.h"
#include "Character.h"
class Weapon{
protected:
	Vector2 * playerPos;
	float damage;
	float range;
	float firerate;
	
	float shootTimer;

public:
	Weapon(float damage, float range, float firerate, Vector2* playerPos){
		this->damage = damage;
		this->range = range;
		this->firerate = firerate;	
		this->shootTimer = 5.0f;	
		this->playerPos = playerPos;
	}

	virtual void shoot(const Vector2& direction) = 0;
	virtual void update(std::deque<std::shared_ptr<Character>>* characters) = 0;
	virtual void draw() = 0;
};
#endif
