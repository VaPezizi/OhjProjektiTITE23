#ifndef _TEXT
#define _TEXT
#include <raylib.h>
#include <string>

class Text{
private:
	std::string text;
	Vector2 position;
	int fontSize;
	Color color;
public:
	Text();
	Text(std::string text, Vector2 pos, int fontSize, Color color);
	std::string& getText();
	void setText(std::string& text);
	void setPos(const float x, const float y);
	void setColor(Color& color);
	void setFontSize(int size);
	void draw();
};

#endif
