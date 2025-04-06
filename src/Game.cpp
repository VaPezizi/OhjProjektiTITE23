#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

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
#include "Scene.h"

//At this point, only initializes window and OpenGL context, but this function will expand
void Game::initGame(const char* windowName){
	InitWindow(this->screenWidth, this->screenHeight, windowName);

	srand(time(NULL));	//Sets the seed for random number generation

	ui = new UIElement(&scenes[currentScene].getCamera(), (Vector2){0, 0});
	soundManager.loadSound("background", "assets/sounds/bg.mp3"); // Load background sound
 	soundManager.playSound("background"); // Play background sound
	
	makeMainMenu();
	//makeMenu2();
	makeGameScene();
	startMainLoop();

}


//Game main loop is here
void Game::startMainLoop(){
	//Player testi = Player((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png", &this->textureManager);
	//addCharacter(Character((float) screenWidth / 2, (float) screenHeight / 2, "assets/testTexture.png"));
	//addPlayer(400.0f, 400.0f, "assets/testTexture.png");
	//addCharacter(Character(screenWidth / 2, screenHeight / 2, "assets/testTexture.png"));

	while(!WindowShouldClose()){	
		//Updating game logic 
		this->updateGame();	
		
		//Drawing the game	
		this->drawGame();
	}
}

void Game::drawHealthBar(int x, int y, int width, int height, int currentHP, int maxHP) {
	float hpPercent = (float)currentHP / maxHP;
	Color barColor;

	if (hpPercent > 0.7f) barColor = GREEN;
	else if (hpPercent > 0.4f) barColor = YELLOW;
	else if (hpPercent > 0.2f) barColor = ORANGE;
	else barColor = RED;

	// Draw bar background (empty)
	DrawRectangle(x, y, width, height, WHITE);

	// Draw filled HP portion
	DrawRectangle(x + 1, y + 1, (int)((width - 2) * hpPercent), height - 2, barColor);

	// Draw border
	DrawRectangleLines(x, y, width, height, BLACK);
}
	

//All drawing should be done in this function
void Game::drawGame(){
	
	/*Menu& menu = this->scenes[currentScene].getMenu();
	std::vector<std::shared_ptr<Character>>& characters = this->scenes[currentScene].getCharacters();*/


	//Starts Draw mode, all draw calls should be made here (if possible)
	//We can draw in other places if needed, but opening draw mode has to be done there then.


	BeginDrawing();
	ClearBackground(WHITE);
	
	

	//menu.draw();
	scenes[currentScene].draw();
	
	

	/*for(std::shared_ptr<Character>& c : characters){
		//c.drawCharacter(&this->textureManager);
		c->drawCharacter();
	}*/	
	EndDrawing();
}

//Put everything you want to do before the game closes here
//(If you use memory, you should free it here, if nowhere else)
void Game::closeGame(){
	this->textureManager.unloadAllTextures();
	for(auto& i:this->scenes){
		i.getCharacters().clear();
	}
	soundManager.unloadAllSounds();
	CloseWindow();
	exit(0);
}

void Game::updateGame(){
	scenes[currentScene].updateCamera(); // Update the camera in the current scene

    for (std::shared_ptr<Character>& character : this->scenes[currentScene].getCharacters()) {
        character->updateCharacter();
    }

    if (IsKeyPressed(KEY_F11)) {
        toggleFullScreen();
    }
	if (currentScene == 0 && IsKeyPressed(KEY_ENTER)) { // entterillä pelaan
        currentScene = 1; 
        isGameRunning = true;
    }

	//Temporary solution for enemy spawning		TODO: Make this good code :D
	if(currentScene == 1){
		spawnTime += GetFrameTime();

		if(spawnTime > difficultyScale){
			Vector2 playerPos = this->scenes[currentScene].getPlayer()->getPosition();
			spawnTime = 0;
			
						
			int x = rand()%10 + 2;	
			int y = rand()%10 + 2;

			if(rand() % 11 < 5)
				x *= -1;
			if(rand() % 11 < 5)
				y *= -1;

			difficultyScale -= 0.1;

			this->scenes[currentScene].addEnemy(playerPos.x + (50 * x), playerPos.y + (50 * y), 0.3f, "assets/poffuTexture.png");
		}
	}

	//TODO: Ehkä tän vois laittaa omaan funktioon, tai jopa menu luokkaan samalla lailla, kun piirto

	for(Nappi& n : this->scenes[currentScene].getMenu().getButtons()){
		if(n.isClicked()){
			if(n.getText() == "start"){
				currentScene = 1;
				isGameRunning = true;
			}
			if(n.getText() == "exit" && !isGameRunning){
				//currentScene = 1;
				closeGame();
			}
			else if(n.getText() == "exit"){
				isGameRunning = false;
				currentScene = 0;
			}
			if(n.getText() == "resize"){
				toggleFullScreen();
			}
		}
		
	}

}

	//TODO: Ehkä tän vois laittaa omaan funktioon, tai jopa menu luokkaan samalla lailla, kun piirto

/*void Game::addCharacter(Character& character){
	this->scenes[currentScene].getCharacters().push_back(character);
}*/


/*
 * Lisää pelaajan.
 * Huomiona, että nykyään hahmot ovat pointtereina, jolloin listan olioita voidaan käsitellä
 * Characterin alaluokkien olioina.
 * Tämä toiminnallisuus tulee vain pointtereilla
 */
/*
void Game::addPlayer(float posX, float posY, const char* fileName){
	this->scenes[currentScene].getCharacters().push_back(
		std::shared_ptr<Character>(new Player{posX, posY, fileName, &this->textureManager}));
}

void Game::addCharacter(float posX, float posY, const char* fileName){
	this->scenes[currentScene].getCharacters().push_back(
		std::shared_ptr<Character>(new Character{posX, posY, fileName, &this->textureManager}));
}
*/
void Game::resetToMainMenu() {
	currentScene = 0;
	//camera.offset = {0.0f, 0.0f};
	//camera.target = {0.0f, 0.0f};
}

//Pelin "pää scene"
void Game::makeGameScene(){

	scenes.push_back(Scene(&this->textureManager));
	Scene& scene = scenes.back();

	Menu& menu = scene.getMenu();
	//menu.addButton(Nappi(100, 50, 150, 50, "resize", BLUE));	
	menu.addButton(Nappi(100, 150, 150, 50, "exit", RED));	

	scene.addPlayer(400.0f, 400.0f, "assets/testTexture.png");
	scene.addEnemy(450.0f, 450.0f, 0.3f, "assets/poffuTexture.png"); 
	scene.setBackground("assets/grassTexture.png");
}

void Game::makeMenu2(){
	scenes.push_back(Scene(&this->textureManager));
	Menu& menu = scenes[currentScene + 1].getMenu();
	menu.addButton(Nappi(100, 250, 150, 50, "pause", ORANGE));
	menu.addButton(Nappi(100, 50, 150, 50, "resize", BLUE));	
	menu.addButton(Nappi(100, 150, 150, 50, "exit", RED));	

	//isGameRunning = true;
	//currentScene = 1;

	} 

void Game::makeMainMenu(){

	scenes.push_back(Scene(&this->textureManager));
	Menu& menu = scenes[currentScene].getMenu();
	menu.addButton(Nappi(200, 150, 150, 50, "start", GREEN)); 
	menu.addButton(Nappi(200, 250, 150, 50, "exit", RED)); 
	menu.addButton(Nappi(200, 350, 150, 50, "resize", BLUE)); 

	menu.addText(Text("Hello World", (Vector2){200, 200}, 16, BLACK));
	isGameRunning = false;
	
	currentScene = 0;
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

    for (Nappi& n : this->scenes[currentScene].getMenu().getButtons()) {
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



