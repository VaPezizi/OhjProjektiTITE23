#include "Game.h"
#include "Character.h"
#include <iostream>

#ifndef _VECTOR
#define _VECTOR
#include <vector>
#endif

#ifndef _CHARACTER
#define _CHARACTER
#include "Character.h"
#endif

#include "Menu.h"
#include "Text.h"
#include "Nappi.h"

// Create buttons		//TODO: Tehdään joku menu luokka tai joku semmonen johna tehdään napit.
//Nappi startButton(200, 150, 150, 50, "start", GREEN);
//Nappi exitButton(200, 250, 150, 50, "exit", RED);
//Nappi resizeButton(200, 350, 150, 50, "resize", BLUE);

//At this point, only initializes window and OpenGL context, but this function will expand
void Game::initGame(const char* windowName){
	InitWindow(this->screenWidth, this->screenHeight, windowName);
	soundManager.loadSound("background", "assets/sounds/bg.mp3"); // Load background sound
 	soundManager.playSound("background"); // Play background sound
					      
	this->menu = Menu();
	menu.addButton(Nappi(200, 150, 150, 50, "start", GREEN)); 
	menu.addButton(Nappi(200, 250, 150, 50, "exit", RED)); 
	menu.addButton(Nappi(200, 350, 150, 50, "resize", BLUE)); 

	menu.addText(Text("Hello World", (Vector2){200, 200}, 16, BLACK));

	startMainLoop();

	}


//Game main loop is here
void Game::startMainLoop(){
	Character testi = Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png", &this->textureManager);
	//addCharacter(Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png"));
	addCharacter(testi);
	//addCharacter(Character(screenWidth / 2, screenHeight / 2, "assets/testTexture.png"));

	while(!WindowShouldClose()){	
		//Updating game logic 
		this->updateGame();	
		
		//Drawing the game	
		this->drawGame();
		}
	}



//All drawing should be done in this function
void Game::drawGame(){

	//Starts Draw mode, all draw calls should be made here (if possible)
	//We can draw in other places if needed, but opening draw mode has to be done there then.

	BeginDrawing();
	ClearBackground(WHITE);

	if (!isGameRunning) {
		for (Nappi& n : this->menu.getButtons()) {
			n.draw();
		}
		for (Text& t : this ->menu.getTexts()) {
			t.draw();
		}
	} 
	// Draw buttons
	/*
	startButton.draw();
	exitButton.draw();
	resizeButton.draw();
	*/

	for(Nappi& n : this->menu.getButtons()){
		n.draw();	
	}
	for(Text& t : this->menu.getTexts()){
		t.draw();
	}

	//DrawText("Hello World", this->screenWidth / 2, this->screenHeight / 2, 20, BLACK);

	for(Character& c : this->characters){
		//c.drawCharacter(&this->textureManager);
		c.drawCharacter();
	}	
	EndDrawing();
}

//Put everything you want to do before the game closes here
//(If you use memory, you should free it here, if nowhere else)
void Game::closeGame(){
	this->textureManager.unloadAllTextures();
	this->characters.clear();
	soundManager.unloadAllSounds();
	CloseWindow();
}

void Game::updateGame(){
	this->characters.front().moveCharacter(-1.0f, 0.0f); // Move the first character

	if (IsKeyPressed(KEY_F11)) { // If F11 is pressed
		std::cout << "F11 painettu - Vaihdetaan ikkunan tilaa" << std::endl;
		toggleFullScreen(); // Toggle fullscreen
	}
	
		if (!isGameRunning) {  
			for (Nappi& n : this->menu.getButtons()) { // Check if any button is clicked during the main menu
				if (n.isClicked()) { // If button is clicked
					std::cout << "Nappi painettu: " << n.getText() << std::endl; // 🔍 DEBUG
	
					if (n.getText() == "start") { // If start button is clicked
						std::cout << "Start button clicked - Peli alkaa!" << std::endl; //  DEBUG
						isGameRunning = true; // Set game running to true
						menu.removeStartButton(); // Remove start button
						menu.moveButtonsToTop(); // Move buttons to top
						lastResizeTime = GetTime(); // Set last resize time
					}
					else if (n.getText() == "exit") { // If exit button is clicked
						std::cout << "Exit button clicked - Suljetaan sovellus" << std::endl;
						exit(0); // Exit the application
					}
					else if (n.getText() == "resize") { // If resize button is clicked
						std::cout << "Resize button clicked - Vaihdetaan ikkunan tila" << std::endl;
						toggleFullScreen(); // Toggle fullscreen
					}
				}
			}
		} 
		else {  
			for (Nappi& n : this->menu.getButtons()) { // Check if any button is clicked during the game
				if (n.isClicked()) { // If button is clicked
					std::cout << "Pelin aikana Nappi painettu: " << n.getText() << std::endl; // 🔍 DEBUG
	
					if (n.getText() == "exit") { // If exit button is clicked
						std::cout << "Exit button clicked - Palataan aloitusvalikkoon!" << std::endl;
						resetToMainMenu(); // Reset to main menu
					}
					else if (n.getText() == "resize") { // If resize button is clicked
						std::cout << "Resize button clicked - Vaihdetaan ikkunan tila pelin aikana" << std::endl;
						toggleFullScreen(); // Toggle fullscreen
					}
				}
			}
		}
	}


void Game::addCharacter(Character& character){
	this->characters.push_back(character);
}
void Game::addCharacter(float posX, float posY, const char* fileName){
	this->characters.push_back((Character){posX, posY, fileName, &this->textureManager});
}

void Game::resetToMainMenu() {
	isGameRunning = false;
	menu = Menu();
	menu.addButton(Nappi(200, 150, 150, 50, "start", GREEN));
	menu.addButton(Nappi(200, 250, 150, 50, "exit", RED));
	menu.addButton(Nappi(200, 350, 150, 50, "resize", BLUE));
	menu.addText(Text("Hello World", (Vector2){200, 200}, 16, BLACK));
}

void Game::toggleFullScreen() {
    std::cout << "toggleFullScreen() kutsuttu!" << std::endl;

    if (IsWindowFullscreen()) { 
        std::cout << "Ikkuna on jo koko ruudussa. Palautetaan alkuperäinen koko." << std::endl;
        ToggleFullscreen();
        SetWindowSize(screenWidth, screenHeight);
        SetWindowPosition(windowPosX, windowPosY);
    } else { 
        std::cout << "Ikkuna EI ole koko ruudussa. Vaihdetaan aitoon koko ruudun tilaan." << std::endl;
        
        ClearWindowState(FLAG_WINDOW_UNDECORATED); 

        int monitor = GetCurrentMonitor();
        int monitorWidth = GetMonitorWidth(monitor);
        int monitorHeight = GetMonitorHeight(monitor);
        
        SetWindowSize(monitorWidth, monitorHeight);
        ToggleFullscreen();
    }

    updateButtonPositions(); // 🔹 Päivitetään nappien paikat, kun ruudun koko muuttuu!
}


void Game::updateButtonPositions() {
    int screenWidth = GetScreenWidth();   // Haetaan nykyinen ruudun leveys
    int screenHeight = GetScreenHeight(); // Haetaan nykyinen ruudun korkeus

    std::cout << "Päivitetään nappien sijainnit: " << screenWidth << "x" << screenHeight << std::endl;

    for (Nappi& n : this->menu.getButtons()) {
        if (n.getText() == "start") {
            n.setPosition(screenWidth / 2 - 75, screenHeight / 2 - 100); // Keskitetään
        } 
        else if (n.getText() == "exit") {
            n.setPosition(screenWidth / 2 - 75, screenHeight / 2); // Keskitetään start-napin alle
        }
        else if (n.getText() == "resize") {
            n.setPosition(screenWidth / 2 - 75, screenHeight / 2 + 100); // Keskitetään vielä alemmas
        }
    }
}



