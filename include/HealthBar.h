#include "UIElement.h"
#include <raylib.h>

class HealthBar : public UIElement{
private:
	//Tänne tarvittavia (Esim itse hp yms)
	Vector2 position;
public:
	//Nämä vain esimerkkinä laitettu
	HealthBar(Camera2D * camera, int maxHp, Vector2 position): UIElement(camera, position){
		this->position = position;
	}
	void removeHP(const int amount);
	void addHP(const int amount);
	virtual void draw();
};
