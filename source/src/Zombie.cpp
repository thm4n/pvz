#include "inc/Zombie.hpp"

Zombie::Zombie(int r, int c) : Entity(r, c, 10) {}

Zombie::~Zombie() {}

void Zombie::update() {
    col -= 1;  // Move left each tick
}

char Zombie::getSymbol() { return 'Z'; }
