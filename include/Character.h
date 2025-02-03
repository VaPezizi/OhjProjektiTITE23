#ifndef _RAYLIB
#include <raylib.h>
#define _RAYLIB
#endif
#include <iostream> //TODO: Poista tää
class Character{
/*private: 
	Character & operator=(const Character&) = delete;
	Character(const Character&) = delete;
*/	
protected: 
	Vector2 position;
	Texture2D texture;

public:
	Character(const float& posX, const float& posY, const char* textureFileName){
		this->position = (Vector2){posX, posY};
		this->texture = LoadTexture(textureFileName);
	}
	~Character(){
		UnloadTexture(texture);
	}
	Character & operator=(const Character&){
		std::cout << "MORO\n";
		return *this;
	}
	void drawCharacter();
};
