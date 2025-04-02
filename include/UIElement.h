#include <raylib.h>

class UIElement{
protected:
	Vector2 position;
	Camera2D * cam;
public:
	UIElement(Camera2D * camera, Vector2 position){
		this->cam = camera;
		this->position = position;
	}
	virtual void draw();
};
