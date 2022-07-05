#pragma once
#include "personaje.h"
#include <iostream>
using namespace std;

class CortoAlcance : public Personajes {
private:
    int NumberSplash;
    int objetiveRange;
    int numCharacter;
public:
    CortoAlcance(bool propery, int num): numCharacter(num), NumberSplash(0), objetiveRange(0) {
        isMine = propery;
        string nameCH = to_string(numCharacter);
        if (isMine)
            nameCH = "mine_" + nameCH;
        else
            nameCH = "enemy_" + nameCH;
        nameCH = "Personajes/" + nameCH;
        obj.setBitmap(nameCH, ".png");
        
    }
    void atacar(){}
    void perderVida(){}
};