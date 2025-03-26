#ifndef _WEAPON
#define _WEAPON
#include <string>

//TODO: koko luokka pitää toteuttaa, tein vaan nopeesti tän nii saa ton inventory slotin tehtyä
class Weapon{
private:
	float damage;
	float range;
	float firerate;
	std::string weaponTexture;
public:
	Weapon(float damage, float range, float firerate, std::string weaponTexture){
		this->damage = damage;
		this->range = range;
		this->firerate = firerate;	
		this->weaponTexture = weaponTexture;
	}

	void shoot();
};
#endif
