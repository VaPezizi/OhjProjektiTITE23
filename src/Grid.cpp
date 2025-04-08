#include "Grid.h"

Cell * Grid::getCell(int posX, int posY){
	return &this->grid[(posX - this->worldSize) / 20][(posY - this->worldSize) / 20];	
}
