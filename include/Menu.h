#ifndef _MENU
#define _MENU
#include <raylib.h>
#include <vector>
#include "Nappi.h" 
#include "Text.h"

class Menu{
private: 
	std::vector<Nappi> buttons;
	std::vector<Text> texts;
public: 
	Menu();
	void addButton(const Nappi nappi);
	void addText(const Text text);
	std::vector<Nappi>& getButtons();
	std::vector<Text>& getTexts();
	void removeButtons();
	void removeTexts();
};

#endif
