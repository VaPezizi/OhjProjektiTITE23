#ifndef _SCENE
#define _SCENE
#include <vector>
#include "Menu.h"
#include "Character.h"

class Scene{
private:
	std::vector<Character> characters;
	TextureManager * textureManager;
	Menu menu;
public:
	Scene();
	Scene(Menu& menu, std::vector<Character>&characters);

	std::vector<Character>& getCharacters();
	Menu& getMenu();
	void addCharacter(Character& character);
	void addCharacter(float posX, float posY, const char* fileName);
	void drawScene();
	void updateScene();
};

#endif
