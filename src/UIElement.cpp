#include "UIElement.h"
#include <raylib.h>
#include <string>

void UIElement::setPlayerPosition(const Vector2& playerPos) {
    position = playerPos; // Update the position to the player's position
}

void UIElement::updateTexts() {
    // Calculate HUD coordinates relative to the player's position
    float hudX = position.x - barWidth / 2; // Center horizontally above the player
    float hudY = position.y - 250;          // 250px above the player

    // Update level text
    std::string levelStr = "Level: " + std::to_string(level);
    levelText.setText(levelStr);
    levelText.setPos(hudX + 50, hudY - 40); // Position

    // Update XP text
    std::string xpStr = "XP: " + std::to_string(currentXP) + "/" + std::to_string(xpThreshold);
    xpText.setText(xpStr);
    xpText.setPos(hudX + 50, hudY - 30); // Position

    // Update timer text
    int minutes = displayedTime / 60;
    int seconds = displayedTime % 60;
    std::string timerStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                           (seconds < 10 ? "0" : "") + std::to_string(seconds);
    timerText.setText(timerStr);

    // Center the timer text horizontally
    int textWidth = MeasureText(timerStr.c_str(), 30);
    float timerX = hudX + 25 + (barWidth - textWidth) / 2;
    float timerY = hudY - 20; // Position 
    timerText.setPos(timerX, timerY);
}

void UIElement::draw() {
    // Calculate HUD coordinates relative to the player's position
    float hudX = position.x - barWidth / 2; // Center horizontally above the player
    float hudY = position.y - 250;          // 250px above the player

    // Draw health bar
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

    // Update and draw texts
    updateTexts();
    levelText.draw();
    xpText.draw();
    timerText.draw();
}
