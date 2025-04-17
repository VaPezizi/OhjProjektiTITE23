#ifndef _UIELEMENT
#define _UIELEMENT

#include <raylib.h>
#include <string>
#include "Text.h"
#include <iostream>

class UIElement {
protected:
    Camera2D* cam;    // Viite kameraan (ei muuteta)
    Vector2 position; // Alkuperäinen sijainti (ei muuteta)

    // HUD-tiedot
    int playerHealth = 100;
    int playerMaxHealth = 100;
    
    int level = 1;
    int currentXP = 0;
    int xpThreshold = 40;
    int displayedTime = 0;  // sekunteina

    // Terveyspalkin koko
    float barWidth = 150;
    float barHeight = 20;

    // Text-oliot, joita käytetään HUD-tekstien piirtämiseen
    Text levelText;
    Text xpText;
    Text timerText;

public:
    // Alustetaan jäsenet käyttämällä alustamislistaa.
    UIElement(Camera2D* camera, Vector2 pos)
        : cam(camera),
          position(pos),
          levelText("Level: 0", (Vector2){0,0}, 40, BLACK),
          xpText("XP: 0/0", (Vector2){0,0}, 40, BLACK),
          timerText("00:00", (Vector2){0,0}, 40, BLACK)
    {}

    // Settereitä HUD-datan päivittämiseen
    void setPlayerHealth(int health) { playerHealth = health; }
    void setPlayerMaxHealth(int maxHealth) { playerMaxHealth = maxHealth; }
    void setLevel(int lvl) { level = lvl; }
    void setCurrentXP(int xp) { currentXP = xp; }
    void setXpThreshold(int threshold) { xpThreshold = threshold; }
    void setDisplayedTime(int time) { displayedTime = time; }
    void setPlayerPosition(const Vector2& playerPos); // New method to update player position
    int getCurrentXP() const { return currentXP; }
    int getLevel() const { return level; }
    int getXpThreshold() const { return xpThreshold; }



    int getPlayerHealth() const { return playerHealth; } // Getter for player health
    int getPlayerMaxHealth() const { return playerMaxHealth; } // Getter for player max health
    float getHpPercent() const { return static_cast<float>(playerHealth) / playerMaxHealth; } // Getter for health percentage

    // Päivittää tekstien sisältöä ja sijainteja
    void updateTexts();

    // Piirtää koko HUD:n
    void draw();
};

#endif
