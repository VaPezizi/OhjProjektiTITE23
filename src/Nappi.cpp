#include "Nappi.h"

Nappi::Nappi(float x, float y, float width, float height, std::string text, Color color) { // Constructor
    this->rect = { x, y, width, height }; // Set the rectangle
    this->text = text; // Set the text
    this->color = color; // Set the color
}

void Nappi::draw() { // Draw the button
    DrawRectangleRec(rect, color);  // Draw the rectangle
    DrawText(text.c_str(), rect.x + 10, rect.y + 10, 20, BLACK); // Draw the text
}

bool Nappi::isClicked() { // Check if the button is clicked
    // Return true if the left mouse button is pressed and the mouse is over the button
    return (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect)); 
}