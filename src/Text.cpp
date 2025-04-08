#include "Text.h"
#include <raylib.h>

Text::Text(){
	this->position = (Vector2){0.0f, 0.0f};
	this->text = std::string();
	this->color = BLACK;
	this->fontSize = 16;
}
Text::Text(std::string text, Vector2 pos, int fontSize, Color color){
	this->position = pos;
	this->text = text;
	this->fontSize = fontSize;
	this->color = color;
}
std::string& Text::getText(){
	return this->text;
}
void Text::setText(std::string& text){
	this->text = text;
}
void Text::setPos(const float x, const float y){
	this->position = (Vector2){x, y};
}
void Text::draw(){
    DrawText(this->text.c_str(), (int)this->position.x, (int)this->position.y, this->fontSize, this->color);
}
void Text::setColor(Color& color){
	this->color = color;
}
void Text::setFontSize(int size){
	this->fontSize = size;
}
