#include "Scene.h"
#include <vector>

Scene::Scene(){
	this->characters = std::vector<Character>();
	characters.reserve(50);		
	this->menu = Menu();
}
Scene::Scene(Menu& menu, std::vector<Character>&characters){
	this->menu = menu;
	this->characters = characters;
}
void Scene::addCharacter(Character& character){
	this->characters.push_back(character);	
}
void Scene::addCharacter(float posX, float posY, const char* fileName){
	this->characters.push_back((Character){posX,
		posY,
		fileName,
		this->textureManager
	});
}
Menu& Scene::getMenu(){
	return this->menu;
}
std::vector<Character>& Scene::getCharacters(){
	return this->characters;
}
