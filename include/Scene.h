#ifndef _SCENE
#define _SCENE
#include <string>
#include <vector>
#include <deque>
#include "Menu.h"
#include "Character.h"
#include "Player.h"
#include <memory>
#include "raylib.h"
#include "UIElement.h"

class Game;

class Scene {
private:
    std::deque<std::shared_ptr<Character>> characters;
    std::shared_ptr<UIElement> ui; // UI element for the scene
    TextureManager* textureManager;
    Menu menu;
    std::string taustaKuva;
    Texture2D backgroundTexture; // Texture for the background image
    std::shared_ptr<Player> player;
    Camera2D camera; // Camera object
    Game* game = nullptr;

public:
    Scene(TextureManager* textureManager);
    Scene(Menu& menu, std::deque<std::shared_ptr<Character>>& characters, TextureManager* textureManager);
    ~Scene(); // Add destructor to unload the background texture

    std::deque<std::shared_ptr<Character>>* getCharacters();
    Menu& getMenu();
    void addCharacter(std::shared_ptr<Character>& character);
    void addCharacter(float posX, float posY, const char* fileName);
    void draw();
    void updateScene();
    void addPlayer(float posX, float posY, const char* fileName);
    void addPlayer(std::shared_ptr<Player>& player);
    void addEnemy(float posX, float posY, float speed, const char* fileName);
    std::shared_ptr<Player> getPlayer();
    void setBackground(const std::string& fileName); // Method to set the background image
    // Camera-related methods
    void updateCamera(); // Update the camera's target
    Camera2D& getCamera(); // Get the camera object
    //void collisionUpdate();
    void setGame(Game* gamePtr) { this->game = gamePtr; }
    UIElement* getUI() { return ui.get(); }

};

#endif
