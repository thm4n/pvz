#pragma once

#include "Logger.hpp"

#include "Entity.hpp"

class Zombie : public Entity {
public:
    Zombie(int r, int c);
    ~Zombie();

    void update() override;

    char getSymbol() override;
};
