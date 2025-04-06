#include "UIElement.h"
#include <raylib.h>
#include <string>

void UIElement::updateTexts() {
    // Calculate HUD coordinates relative to the camera's visible area
    float hudX = cam->target.x - cam->offset.x + GetScreenWidth() - barWidth - 20; // 20px padding from the right
    float hudY = cam->target.y - cam->offset.y + 20; // 20px padding from the top

    // Update level text
    std::string levelStr = "Level: " + std::to_string(level);
    levelText.setText(levelStr);
    levelText.setPos(hudX, hudY + 25);

    // Update XP text
    std::string xpStr = "XP: " + std::to_string(currentXP) + "/" + std::to_string(xpThreshold);
    xpText.setText(xpStr);
    xpText.setPos(hudX, hudY + 50);

    // Update timer text
    int minutes = displayedTime / 60;
    int seconds = displayedTime % 60;
    std::string timerStr = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" +
                           (seconds < 10 ? "0" : "") + std::to_string(seconds);
    timerText.setText(timerStr);

    // Align the timer text to the right edge of the HUD
    int textWidth = MeasureText(timerStr.c_str(), 30);
    float timerX = hudX + barWidth - textWidth;
    float timerY = hudY;
    timerText.setPos(timerX, timerY);
}

void UIElement::draw() {
    // Calculate HUD coordinates relative to the camera's visible area
    float hudX = cam->target.x - cam->offset.x + GetScreenWidth() - barWidth - 20; // 20px padding from the right
    float hudY = cam->target.y - cam->offset.y + 20; // 20px padding from the top

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
