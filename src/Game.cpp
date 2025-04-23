#include "Game.h"
#include "Character.h"
#include "Player.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>

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
	soundManager.loadSound("doomost", "assets/doom.mp3");
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
void Game::addXP(int xp) {
    if (!ui) return;

    int current = ui->getCurrentXP();
    int level = ui->getLevel();
    int threshold = ui->getXpThreshold();

    current += xp;

    // Tason nousu mahdollisesti useita kertoja
    while (current >= threshold) {
        level++;
        threshold += 40;  // Threshold kasvaa joka tasolla 40 yksikköä
        std::cout << "Level up! Uusi taso: " << level << std::endl;
    }

    // Päivitetään UI:n tila
    ui->setCurrentXP(current);
    ui->setLevel(level);
    ui->setXpThreshold(threshold);
    ui->updateTexts();
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
void Game::createSaveFile(const int amount){
	std::ofstream newFile("record.txt");
	newFile << std::to_string(amount);
	newFile.close();
}
//Returns 1 when new record is achieved
int Game::saveScore(const int amount, std::ifstream& stream, const std::string& fileName){
	std::string fileText;	
	if(stream.peek() == std::ifstream::traits_type::eof()){		//Check for empty file
		stream.close();
		createSaveFile(amount);
		std::cout << "Tehdaan\n";
		return 1;
	}
	while(std::getline(stream, fileText)){
		int record = std::stoi(fileText);
		if(record < this->finalSurvivalTime){
			createSaveFile(amount);
			std::cout << "Uusi ennätys!\n";
			return 1;
		}
	}
	return 0;
	
}
void Game::gameOver(){
	Scene& scene = scenes[currentScene];
	this->scenes[currentScene].getCharacters()->clear();
	scene.addPlayer(400.0f, 400.0f, "assets/testTexture.png");
	scene.addEnemy(500.0f, 500.0f, 0.3f, "assets/poffuTexture.png"); 
	ui->setPlayerHealth(100); // Reset player health to 100
	this->ui->setCurrentXP(0);	//Resetting this to 40
	this->ui->setXpThreshold(40);
	this->ui->setLevel(1);
	
	this->difficultyScale = 5.0f;

	finalSurvivalTime = static_cast<int>(elapsedTime);


	Menu& gameOverMenu = scenes.back().getMenu(); // scenes.back() = Game Over -scene
	int minutes = finalSurvivalTime / 60;
	int seconds = finalSurvivalTime % 60;

	char buffer[32];
	sprintf(buffer, "Selvisit: %02d:%02d", minutes, seconds);
	std::string survivalTextStr(buffer);

	for (Text& t : gameOverMenu.getTexts()) {
		if (t.getText().find("Selvisit:") != std::string::npos) {
			t.setText(survivalTextStr);
			break;
		}
	}


	this->currentScene = scenes.size() - 1;	//Nopeesti tehty tää, viimmene scene on gameover scene, siks size - 1
        isGameRunning = false;


	//Ennätysten tallennus
	std::string fileName = "record.txt";
	std::ifstream file(fileName);
	
	if(file){
		if(saveScore(finalSurvivalTime, file, fileName)){
			//Tiiän et tyhmä käydä kaks kertaa läpi, mut ihan sama.
			//3 kertaa ny :DD (Toisaalta, vaan yks suoritetaan, niin ei kiinnosta)
			for(Text& text : gameOverMenu.getTexts()){
				if(text.getText().find("Ei uutta ennätystä") != std::string::npos){
					std::string onnittelu = "Uusi ennätys, onnittelut :)";
					text.setText(onnittelu);
					break;
				}
			}			
		}else{
			for(Text& text : gameOverMenu.getTexts()){
				if(text.getText().find("Uusi ennätys, onnittelut :)") != std::string::npos){
					std::string onnittelu = "Ei uutta ennätystä";
					text.setText(onnittelu);
					break;
				}
			}	
		}
	}else{
		std::cout << "No file found, creating one\n";
		for(Text& text : gameOverMenu.getTexts()){
				if(text.getText().find("Uusi ennätys, onnittelut :)") != std::string::npos){
					std::string onnittelu = "Ei uutta ennätystä";
					text.setText(onnittelu);
					break;
				}
			}	

				
		createSaveFile(finalSurvivalTime);
	}
}

void Game::updateGame(){
	scenes[currentScene].updateCamera(); // Update the camera in the current scene

	if (ui) {
        ui->updateTexts(); 
    }

	if (isGameRunning) {
		elapsedTime += GetFrameTime();
		if (ui) ui->setDisplayedTime(static_cast<int>(elapsedTime));
	}
	

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
                    ui->setPlayerHealth(health - 20); // Decrease player health 
                    std::cout << "AUTTAKAA, MINUUN OSUI! health: " << ui->getPlayerHealth();
					std::cout << " "<< ui->getHpPercent()<< std::endl;

					//TODO: // HP Prosentti ei näy hudissa

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

            
			if(difficultyScale > 0.5f)	//Max difficulty scale
			       	difficultyScale *= 0.95;

			int num = rand()%360 + 1;		//Random numero väliltä 0 - 360
			float radius = 500.0f; // Define and initialize radius
			Vector2 newPos = (Vector2){(float) playerPos.x + radius * std::cos(num * (PI / 180)),		//Lasketaan spawnattavan vihun sijainti ottamalla
				(float) playerPos.y + radius * std::sin(num * (PI / 180))};				//satunnaisella kulmalla pelaajan ympäriltä sijainnin
																
			this->scenes[currentScene].addEnemy(newPos.x, newPos.y, 0.3f, "assets/poffuTexture.png");

			std::cout << "New pos: X: " << newPos.x << " Y: " << newPos.y << std::endl;

//			this->scenes[currentScene].addEnemy(playerPos.x + (50 * newPos.x), playerPos.y + (50 * y), 0.3f, "assets/poffuTexture.png");
		}
		
	}

    if (currentScene == 1 && IsKeyPressed(KEY_G)) {
        gameOver();
    }

    //TODO: Ehkä tän vois laittaa omaan funktioon, tai jopa menu luokkaan samalla lailla, kun piirto

	for(Nappi& n : this->scenes[currentScene].getMenu().getButtons()){
		if(n.isClicked()){
			if(n.getText() == "start" || n.getText() == "restart"){
				this->soundManager.playSound("doomost");

				currentScene = 1;
				isGameRunning = true;
				resetTimer();
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

	scene.setGame(this);
	this->ui = scene.getUI();

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
	menu.addText(Text("Selvisit: 00:00", (Vector2){200, 250}, 24, WHITE));
	menu.addText(Text("Ei uutta ennätystä :(", (Vector2){200, 275}, 24, WHITE));

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

void Game::resetTimer() {
    elapsedTime = 0.0f;
}

float Game::getElapsedTime() const {
    return elapsedTime;
}




