#include "UIElement.h"
#include <raylib.h>
#include <string>

void UIElement::updateTexts() {
    // Lasketaan paikallisesti HUD-koordinaatit, emmekä muuta cam:ia tai positionia
    float hudX = cam->target.x + (GetScreenWidth() / 2) - 170;
    float hudY = cam->target.y - (GetScreenHeight() / 2) + 20;
    
    // Päivitetään tason teksti ja asetetaan sijainti
    std::string levelStr = "Level: " + std::to_string(level);
    levelText.setText(levelStr);
    levelText.setPos(hudX, hudY + 25);
    
    // Päivitetään XP-teksti ja asetetaan sijainti
    std::string xpStr = "XP: " + std::to_string(currentXP) + "/" + std::to_string(xpThreshold);
    xpText.setText(xpStr);
    xpText.setPos(hudX, hudY + 50);

    // Päivitetään ajastimen teksti
    int minutes = displayedTime / 60;
    int seconds = displayedTime % 60;
    std::string timerStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                           (seconds < 10 ? "0" : "") + std::to_string(seconds);
    timerText.setText(timerStr);
    
    // Aseta ajastimen sijainti keskelle vaakasuunnassa
    int textWidth = MeasureText(timerStr.c_str(), 30);
    float timerX = cam->target.x - (GetScreenWidth() / 2) + ((GetScreenWidth() - textWidth) / 2);
    float timerY = cam->target.y - (GetScreenHeight() / 2) + 20;
    timerText.setPos(timerX, timerY);
}

void UIElement::draw() {
    // Lasketaan paikallisesti HUD-koordinaatit
    float hudX = cam->target.x + (GetScreenWidth() / 2) - 170;
    float hudY = cam->target.y - (GetScreenHeight() / 2) + 20;

    // Piirretään terveyspalkki
    float hpPercent = (float)playerHealth / playerMaxHealth;
    Color barColor = GREEN;
    if (hpPercent > 0.7f)
        barColor = GREEN;
    else if (hpPercent > 0.4f)
        barColor = YELLOW;
    else if (hpPercent > 0.2f)
        barColor = ORANGE;
    else
        barColor = RED;

    DrawRectangle(hudX, hudY, barWidth, barHeight, WHITE);
    DrawRectangle(hudX + 1, hudY + 1, (int)((barWidth - 2) * hpPercent), barHeight - 2, barColor);
    DrawRectangleLines(hudX, hudY, barWidth, barHeight, BLACK);

    // Päivitetään ja piirretään tekstit Text-luokan avulla
    updateTexts();
    levelText.draw();
    xpText.draw();
    timerText.draw();
}
