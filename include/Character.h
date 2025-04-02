#ifndef _RAYLIB
#include <raylib.h>
#define _RAYLIB
#endif
#include <string>
#include <iostream>
#include "TextureManager.h"

#ifndef _CHARACTER
#define _CHARACTER

class Character{
/*private: 
	Character & operator=(const Character&) = delete;
	Character(const Character&) = delete;
*/	
protected: 
	Vector2 position;
	std::string texture;
	TextureManager * textures;

public:
	Character(const float& posX, const float& posY, const std::string& fileName, TextureManager * textures){
		this->position = (Vector2){posX, posY};
		this->texture = fileName;
		this->textures = textures;
		textures->loadTexture(fileName);
	}
	virtual ~Character(){
	}
	Character & operator=(const Character&){
		//std::cout << "MORO\n";
		return *this;
	}
	virtual void drawCharacter();

	//Used to move the character by x and y values. 
	void moveCharacter(float x, float y);

	//Used to update the character.
	virtual void updateCharacter();		//Virtual method that derived classes can override. 

};
#endif
