#include <deque>
#include <memory>
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

private:
    int experiencePoints = 0;
    int level = 1;
    int xpThreshold = 100;


protected: 
	Vector2 position;
	std::string texture;
	TextureManager * textures;
	bool shouldBeKilled;
	Rectangle bbox;

public:
	Character(const float& posX, const float& posY, const std::string& fileName, TextureManager * textures){
		this->position = (Vector2){posX, posY};
		this->texture = fileName;
		this->textures = textures;
		textures->loadTexture(fileName);
		Texture2D texture = textures->getTexture(fileName);
		shouldBeKilled = 0;
		this->bbox = (Rectangle){this->position.x, this->position.y, (float) texture.width, (float) texture.height};
	}
	virtual ~Character(){
	}
	Character & operator=(const Character&){
		//std::cout << "MORO\n";
		return *this;
	}
	virtual void drawCharacter();
	void kill();
	//Used to move the character by x and y values. 
	void moveCharacter(float x, float y);
	Rectangle& getBbox();

	void updateExperience();
    int getExperiencePoints() const { return experiencePoints; }
    int getLevel() const { return level; }
    int getXpThreshold() const { return xpThreshold; }
    void resetStats(); 

	//Used to update the character.
	virtual void updateCharacter(std::deque<std::shared_ptr<Character>>*characters);		//Virtual method that derived classes can override. 
	bool getKilled();
	
};
#endif
