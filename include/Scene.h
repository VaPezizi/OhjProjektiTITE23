#ifndef _SCENE
#define _SCENE
#include <string>
#include <vector>
#include "Menu.h"
#include "Character.h"
#include <memory>

class Scene{		//TODO: Lisää tänne taustakuva hommat
private:
	std::vector<std::shared_ptr<Character>> characters;
	TextureManager * textureManager;
	Menu menu;
	std::string taustaKuva;
public:
	Scene();
	Scene(Menu& menu, std::vector<std::shared_ptr<Character>> & characters);
	std::vector<std::shared_ptr<Character>> & getCharacters();
	Menu& getMenu();
	void addCharacter(std::shared_ptr<Character>& character);
	void addCharacter(float posX, float posY, const char* fileName);
	void drawScene();
	void updateScene();
	
};

#endif
