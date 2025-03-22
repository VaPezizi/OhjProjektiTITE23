#ifndef _ENEMY
#define _ENEMY
#include "Character.h"
#include <memory>
#include <raylib.h>
#include "Player.h"

class Enemy : public Character{

//using Character::Character;
private:
	std::shared_ptr<Player> player;
	float speed;
public:
	Enemy(const float& posX, const float& posY, float speed, const std::string& filename, TextureManager * textures, std::shared_ptr<Player> player):Character(posX, posY, filename, textures){
		this->player = player;
		this->speed = speed;
	}
	Vector2 getPosition() const;// {
        //return this->position;
    	//}
	virtual void updateCharacter();
	
	virtual ~Enemy();
};

#endif
