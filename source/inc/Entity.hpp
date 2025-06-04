#pragma once

#include "Logger.hpp"

class Entity {
public:
	int row, col;
	int health;

	Entity(int r, int c, int hp) : row(r), col(c), health(hp) {}
	virtual void update() = 0;
	virtual char getSymbol() = 0;
	virtual ~Entity() {}
};
