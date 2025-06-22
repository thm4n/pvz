#pragma once

#include "Entity.hpp"
#include "Logger.hpp"

class Plant : public Entity {
public:
    int shootCooldown;

    Plant(int r, int c);
    ~Plant();

    void update() override;

    char getSymbol() override;
};
