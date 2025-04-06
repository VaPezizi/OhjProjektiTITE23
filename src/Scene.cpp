#include "Scene.h"
#include "raylib.h"
#include "Weapon.h"
#include "Player.h"
#include "TextureManager.h"
#include <vector>
#include <memory>
#include "Enemy.h"
#include <cmath> // For floor function
#include "UIElement.h"

Scene::Scene(TextureManager* textureManager) { // TODO: Lisää tänne taustakuva
    this->ui = std::make_shared<UIElement>(&camera, (Vector2){0, 0});
    this->characters = std::vector<std::shared_ptr<Character>>();
    characters.reserve(50);
    this->menu = Menu();
    this->textureManager = textureManager;
    this->backgroundTexture = { 0 }; // Initialize background texture
	camera.target = { 0.0f, 0.0f }; // Default target position
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() /2 }; // Center of the screen
    camera.rotation = 0.0f;         // No rotation
    camera.zoom = 1.0f;             // Default zoom level

}

Scene::~Scene() {
    if (backgroundTexture.id > 0) {
        UnloadTexture(backgroundTexture); // Unload the background texture
    }
}

Scene::Scene(Menu& menu, std::vector<std::shared_ptr<Character>>& characters, TextureManager* textureManager) {
    this->menu = menu;
    this->characters = characters;
    this->textureManager = textureManager;
    this->backgroundTexture = { 0 }; // Initialize background texture
}

void Scene::setBackground(const std::string& fileName) {
    taustaKuva = fileName;
    if (backgroundTexture.id > 0) {
        UnloadTexture(backgroundTexture); // Unload the previous texture if it exists
    }
    backgroundTexture = LoadTexture(fileName.c_str()); // Load the new background texture
    if (backgroundTexture.id == 0) {
        std::cerr << "Failed to load background image: " << fileName << std::endl;
    }
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

void Scene::updateCamera() {
    if (player) {
        camera.target = player->getPosition(); // Update the camera target to follow the player     
    }else{
        camera.target = camera.offset; // Default target position if no player is set
    }

    // Update the camera offset to center the screen
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    
}

Camera2D& Scene::getCamera() {
    return camera;
}

void Scene::draw() {
    BeginMode2D(camera); // Start drawing with the camera

    if (backgroundTexture.id > 0) {
        // Get the camera's visible area
        float cameraLeft = camera.target.x - camera.offset.x / camera.zoom;
        float cameraTop = camera.target.y - camera.offset.y / camera.zoom;
        float cameraRight = cameraLeft + GetScreenWidth() / camera.zoom;
        float cameraBottom = cameraTop + GetScreenHeight() / camera.zoom;

        // Calculate the size of the background texture
        int tileWidth = backgroundTexture.width;
        int tileHeight = backgroundTexture.height;

        // Calculate the range of tiles to draw
        int startX = static_cast<int>(floor(cameraLeft / tileWidth));
        int startY = static_cast<int>(floor(cameraTop / tileHeight));
        int endX = static_cast<int>(ceil(cameraRight / tileWidth));
        int endY = static_cast<int>(ceil(cameraBottom / tileHeight));

        // Draw the tiles
        for (int x = startX; x < endX; ++x) {
            for (int y = startY; y < endY; ++y) {
                DrawTexture(backgroundTexture, x * tileWidth, y * tileHeight, WHITE);
            }
        }
    }

    // Draw the menu and characters
    this->menu.draw();
    for (std::shared_ptr<Character>& c : this->characters) {
        c->drawCharacter();
    }

    // Draw HUD (UI)
    ui->draw();

    EndMode2D(); // End drawing with the camera
}
std::vector<std::shared_ptr<Character>>& Scene::getCharacters(){
	return this->characters;
}
std::shared_ptr<Player> Scene::getPlayer(){
	return this->player;
}
