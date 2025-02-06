#ifndef NAPPI_H 
#define NAPPI_H 

#include "raylib.h"
#include <string>

class Nappi { // Button class
public:
    Nappi(float x, float y, float width, float height, std::string text, Color color); // Constructor
    void draw();  // Draw the button
    bool isClicked(); // Check if the button is clicked

private: 
    Rectangle rect; // Rectangle of the button
    std::string text; // Text of the button
    Color color; // Color of the button
};

#endif
