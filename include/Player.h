#ifndef _PLAYER
#define _PLAYER
#include "Character.h"
#include <raylib.h>
#include <vector>
#include "Weapon.h"

class Player : public Character{

//using Character::Character;
private:
	//std::vector<Weapon>weapons;	
	int inventorySpace;

public:
	Player();
	Player(const float& posX, const float& posY, const std::string& filename, TextureManager * textures):Character(posX, posY, filename, textures){
		//Varataan muistia 5 aseelle
	//	weapons.reserve(5);	
		this->inventorySpace = 5;
	}
	Vector2 getPosition() const ;//{
//        return this->position;
 //   }
	virtual void updateCharacter();
	void addWeapon(const Weapon& weapon);
	//const std::vector<Weapon>& getWeapons();
	//const int& getInventorySpace();	
	virtual ~Player();
};

#endif
