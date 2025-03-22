#include "Scene.h"
#include "Player.h"
#include "TextureManager.h"
#include <vector>
#include <memory>
#include "Enemy.h"

Scene::Scene(TextureManager * textureManager){		//TODO: Lisää tänne taustakuva 
	this->characters = std::vector<std::shared_ptr<Character>>();
	characters.reserve(50);		
	this->menu = Menu();
	this->textureManager = textureManager;
}

//Muutettu shared_ptr:ksi, että saamme kunnon olio ajattelu tyylisen toiminnallisuuden character luokkaan.

Scene::Scene(Menu& menu, std::vector<std::shared_ptr<Character>>&characters, TextureManager * textureManager){
	this->menu = menu;
	this->characters = characters;
	this->textureManager = textureManager;
}
void Scene::addCharacter(std::shared_ptr<Character>& character){
	this->characters.push_back(character);	
}
void Scene::addPlayer(std::shared_ptr<Player>& character){
	this->characters.push_back(character);	
	player = character;
}
void Scene::addPlayer(float posX, float posY, const char* fileName){
	std::shared_ptr<Player> c(new Player(posX,
		posY,
		fileName,
		this->textureManager
		));

	//std::cout << "MORO\n";
	this->characters.push_back(c);
	player = c;
}

void Scene::addEnemy(float posX, float posY, float speed, const char* fileName){
	std::shared_ptr<Enemy> c(new Enemy(
		posX,
		posY,
		speed,
		fileName,
		this->textureManager,
		this->player
		));

	//std::cout << "MORO\n";
	this->characters.push_back(c);

}
void Scene::addCharacter(float posX, float posY, const char* fileName){
	std::shared_ptr<Character> c(new Character(posX,
		posY,
		fileName,
		this->textureManager
		));

	this->characters.push_back(c);
	/*this->characters.push_back((Character){posX,
		posY,
		fileName,
		this->textureManager
	});*/
}
Menu& Scene::getMenu(){
	return this->menu;
}
std::vector<std::shared_ptr<Character>>& Scene::getCharacters(){
	return this->characters;
}
