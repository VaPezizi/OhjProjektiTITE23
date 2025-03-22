#ifndef _PLAYER
#define _PLAYER
#include "Character.h"
#include <raylib.h>


class Player : public Character{

//using Character::Character;


public:
	Player();
	Player(const float& posX, const float& posY, const std::string& filename, TextureManager * textures):Character(posX, posY, filename, textures){

	}
	Vector2 getPosition() const ;//{
//        return this->position;
 //   }
	virtual void updateCharacter();
	
	virtual ~Player();
};

#endif
