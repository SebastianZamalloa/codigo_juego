#pragma once
#include "character.h"
#include <iostream>
using namespace std;

class shortRange : public character {
private:
    int NumberSplash;
    int objetiveRange;
public:
    shortRange(int auxID, bool propery) :character(auxID, propery)
    {
        NumberSplash = 0; //DB
        objetiveRange = 0; //DB
    }
    ~shortRange(){}
    void atacar(){}
};