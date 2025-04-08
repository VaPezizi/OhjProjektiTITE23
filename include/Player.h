#ifndef _PLAYER
#define _PLAYER
#include "Character.h"
#include <deque>
#include <memory>
#include <raylib.h>
#include <vector>
#include "Weapon.h"
#include "Wand.h"

class Player : public Character{

//using Character::Character;
private:
	std::vector<std::shared_ptr<Weapon>>weapons;	
	int inventorySpace;

public:
	Player();
	Player(const float& posX, const float& posY, const std::string& filename, TextureManager * textures):Character(posX, posY, filename, textures){
		//Varataan muistia 5 aseelle
	//	weapons.reserve(5);	
		this->inventorySpace = 5;
		this->weapons.push_back(std::shared_ptr<Weapon>(new Wand(5.0f, 10.0f, 0.5f, &this->position)));
	}
	Vector2 getPosition();//{
//        return this->position;
 //   }
	virtual void updateCharacter(std::deque<std::shared_ptr<Character>>*characters) override;
	void addWeapon(const Weapon& weapon);
	const std::vector<Weapon>& getWeapons();
	const int& getInventorySpace();	
	void drawCharacter() override;
	virtual ~Player();
};

#endif
