#ifndef _PROJECTILE
#define _PROJECTILE
#include "raylib.h"
#include "Character.h"
#include <deque>
#include <memory>
#include <vector>

class Projectile{
private:
	Vector2 position;
	Vector2 direction;
	float width;
	float timeAlive;			//ammuksen range
	float speed;
	bool shouldBeKilled;
public:

	Projectile(Vector2& position, const Vector2& direction, const float& width, const float & speed, const float& timeAlive){
		this->position = position;
		this->width =width;
		this->direction = direction;
		this->speed = speed;
		this->timeAlive = timeAlive;
		shouldBeKilled = 0;

	}
	int update(std::deque<std::shared_ptr<Character>>* characters);
	void draw();
};

#endif
