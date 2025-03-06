#include "Scene.h"
#include <vector>
#include <memory>

Scene::Scene(){		//TODO: Lisää tänne taustakuva 
	this->characters = std::vector<std::shared_ptr<Character>>();
	characters.reserve(50);		
	this->menu = Menu();
}

//Muutettu shared_ptr:ksi, että saamme kunnon olio ajattelu tyylisen toiminnallisuuden character luokkaan.

Scene::Scene(Menu& menu, std::vector<std::shared_ptr<Character>>&characters){
	this->menu = menu;
	this->characters = characters;
}
void Scene::addCharacter(std::shared_ptr<Character>& character){
	this->characters.push_back(character);	
}
void Scene::addCharacter(float posX, float posY, const char* fileName){
	std::shared_ptr<Character> c(new Character(posX,
		posY,
		fileName,
		this->textureManager
		));
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
