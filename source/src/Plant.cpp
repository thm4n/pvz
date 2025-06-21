#include "inc/Plant.hpp"

Plant::Plant(int r, int c) : Entity(r, c, 5), shootCooldown(0) {

}

Plant::~Plant() {

}

void Plant::update() {
	if(shootCooldown > 0)
		shootCooldown--;
}

char Plant::getSymbol() {
	return 'P';
}
