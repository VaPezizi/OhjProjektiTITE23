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
    makeGameOverScene();
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
		i.getCharacters()->clear();
	}
	soundManager.unloadAllSounds();
	CloseWindow();
	exit(0);
}
void Game::gameOver(){
	Scene& scene = scenes[currentScene];
	this->scenes[currentScene].getCharacters()->clear();
	scene.addPlayer(400.0f, 400.0f, "assets/testTexture.png");
	scene.addEnemy(500.0f, 500.0f, 0.3f, "assets/poffuTexture.png"); 
	ui->setPlayerHealth(100); // Reset player health to 100


	this->currentScene = scenes.size() - 1;	//Nopeesti tehty tää, viimmene scene on gameover scene, siks size - 1
        isGameRunning = false;
	
}

void Game::updateGame() {
    scenes[currentScene].updateCamera(); // Update the camera in the current scene

    if (IsKeyPressed(KEY_F11)) {
        toggleFullScreen();
    }
    if (currentScene == 0 && IsKeyPressed(KEY_ENTER)) { // entterillä pelaan
        currentScene = 1; 
        isGameRunning = true;
    }

    //Temporary solution for enemy spawning		TODO: Make this good code :D
    if (currentScene == 1) {
        std::shared_ptr<Player> player = scenes[currentScene].getPlayer();
        std::deque<std::shared_ptr<Character>>& characters = *this->scenes[currentScene].getCharacters();
        for (auto it = characters.begin(); it != characters.end();) {
            if ((*it) != player) {
                if (CheckCollisionRecs(player->getBbox(), (*it)->getBbox())) {
                    int health = ui->getPlayerHealth(); // Get current player health
                    ui->setPlayerHealth(health - 50); // Decrease player health 
                    std::cout << "AUTTAKAA, MINUUN OSUI! health: " << ui->getPlayerHealth();
					std::cout << " "<< ui->getHpPercent()<< std::endl;

					TODO: // HP Prosentti ei näy hudissa

                    (*it)->kill(); // Kill the enemy after

                    if (ui->getPlayerHealth() <= 0) {
                        gameOver(); // Call game over logic after the loop
            			return;
                    }
                }
            }

            (*it)->updateCharacter(&characters);

            if ((*it)->getKilled()) {
                it = characters.erase(it);
            } else {
                ++it;
            }
        }



        spawnTime += GetFrameTime();

        if (spawnTime > difficultyScale) {
            Vector2 playerPos = this->scenes[currentScene].getPlayer()->getPosition();
            spawnTime = 0;

            int x = rand() % 10 + 2;	
            int y = rand() % 10 + 2;

            if (rand() % 11 < 5)
                x *= -1;
            if (rand() % 11 < 5)
                y *= -1;

            difficultyScale -= 0.1;

            this->scenes[currentScene].addEnemy(playerPos.x + (50 * x), playerPos.y + (50 * y), 0.3f, "assets/poffuTexture.png");
        }
    }

    if (currentScene == 1 && IsKeyPressed(KEY_G)) {
        gameOver();
    }

    //TODO: Ehkä tän vois laittaa omaan funktioon, tai jopa menu luokkaan samalla lailla, kun piirto

    for (Nappi& n : this->scenes[currentScene].getMenu().getButtons()) {
        if (n.isClicked()) {
            if (n.getText() == "start" || n.getText() == "restart") {
                currentScene = 1;
                isGameRunning = true;
            }
            if (n.getText() == "exit" && !isGameRunning) {
                closeGame();
            } else if (n.getText() == "exit") {
                isGameRunning = false;
                currentScene = 0;
            }
            if (n.getText() == "resize") {
                toggleFullScreen();
            }
        }
    }
}

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

	scene.addPlayer(400.0f, 400.0f, "assets/testTexture.png");
	scene.addEnemy(500.0f, 500.0f, 0.3f, "assets/poffuTexture.png"); 
	scene.setBackground("assets/grassTexture.png");
}

void Game::makeGameOverScene() {
    scenes.push_back(Scene(&this->textureManager));
    Scene& scene = scenes.back();

    // Lisää Game Over -teksti ja napit
    Menu& menu = scene.getMenu();
    menu.addText(Text("Game Over", (Vector2){200, 200}, 64, RED));
    menu.addButton(Nappi(200, 300, 150, 50, "restart", GREEN));
    menu.addButton(Nappi(400, 300, 150, 50, "exit", RED));
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
}