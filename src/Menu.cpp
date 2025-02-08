#include "Menu.h"
#include <vector>

Menu::Menu(){
	this->buttons = std::vector<Nappi>();
	this->texts = std::vector<Text>();
}
void Menu::addButton(const Nappi nappi){
	buttons.push_back(nappi);	
}
void Menu::addText(const Text text){
	texts.push_back(text);
}
std::vector<Nappi>& Menu::getButtons(){
	return this->buttons;
}
std::vector<Text>& Menu::getTexts(){
	return this->texts;
}
void Menu::removeButtons(){
	this->texts.clear();
}
void Menu::removeTexts(){
	this->texts.clear();
}
