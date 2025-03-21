#ifndef _SCENE
#define _SCENE
#include <string>
#include <vector>
#include "Menu.h"
#include "Character.h"
#include "Player.h"
#include <memory>

class Scene{		//TODO: Lisää tänne taustakuva hommat
private:
	std::vector<std::shared_ptr<Character>> characters;
	TextureManager * textureManager;
	Menu menu;
	std::string taustaKuva;
public:
	Scene(TextureManager * textureManager);
	Scene(Menu& menu, std::vector<std::shared_ptr<Character>> & characters, TextureManager * textureManager);
	std::vector<std::shared_ptr<Character>> & getCharacters();
	Menu& getMenu();
	void addCharacter(std::shared_ptr<Character>& character);
	void addCharacter(float posX, float posY, const char* fileName);
	void drawScene();
	void updateScene();
	void addPlayer(float posX, float posY, const char* fileName);
	void addPlayer(std::shared_ptr<Player>& player);
	
};

#endif
