#include "Menu.h"
#include <vector>
#include <algorithm>
#include <iostream>

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
	this->buttons.clear();
}
void Menu::removeTexts(){
	this->texts.clear();
}

void Menu::moveButtonsToTop(){ // Move buttons to top
	for (Nappi& n : this->buttons) { // Loop through buttons
		if (n.getText() == "exit") { // If exit button
			n.setPosition(10, 10); // Set position
		}
		else if (n.getText() == "resize") { // If resize button
			n.setPosition(120, 10); // Set position
		}
	}
}

void Menu::removeStartButton() { // Remove start button
    buttons.erase(std::remove_if(buttons.begin(), buttons.end(), 
        [](const Nappi& n) { return n.getText() == "start"; }), buttons.end());
}

void Menu::draw(){
	for(Nappi& n : this->buttons){
		n.draw();	
	}
	for(Text& t: this->texts){
		t.draw();
	}
}

