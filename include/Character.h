#ifndef _RAYLIB
#include <raylib.h>
#define _RAYLIB
#endif
#include <string>

#include "TextureManager.h"

#ifndef _CHARACTER
#define _CHARACTER

class Character{
/*private: 
	Character & operator=(const Character&) = delete;
	Character(const Character&) = delete;
*/	

private:
    int experiencePoints = 0;
    int level = 1;
    int xpThreshold = 100;


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

	~Character(){
	}
	Character & operator=(const Character&){
		//std::cout << "MORO\n";
		return *this;
	}
	void drawCharacter();

	//Used to move the character by x and y values. 
	void moveCharacter(float x, float y);

	void updateExperience();
    int getExperiencePoints() const { return experiencePoints; }
    int getLevel() const { return level; }
    int getXpThreshold() const { return xpThreshold; }
    void resetStats(); 
};
#endif
