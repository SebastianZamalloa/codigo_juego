#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"
#include <string>

class Personajes
{
    protected:
        int increment;
        int HP;
        bool isMine;
        int range;
        float attackSpeed;
        float speedMovemement;
        int damage;
        bool areaDamage;
        int price;
        int level;
        image obj;
    public:
        Personajes() { HP = range = attackSpeed = speedMovemement = damage = areaDamage = price = level = 0; increment = 0; }
        virtual void atacar() = 0;
        void avanzar() { if (isMine)increment++; else { increment--; } }
        virtual void perderVida() = 0;
        void generateCharacter(int x, int y) { obj.generateImage(x+=increment, y); avanzar(); }
};

