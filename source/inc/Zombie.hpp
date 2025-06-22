#pragma once

#include "Entity.hpp"
#include "Logger.hpp"

class Zombie : public Entity {
public:
    Zombie(int r, int c);
    ~Zombie();

    void update() override;

    char getSymbol() override;
};
