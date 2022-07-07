#pragma once
#include <mysql.h>
#include <iostream>
#include "image.h"
#include <string>
#include "conexion.cpp"

struct baseCharacter
{
    int HP;
    int range;
    float attackSpeed;
    float speedMovemement;
    int damage;
    bool areaDamage;
    int price;
    int level;
};

class character
{
    protected:
        int ID;
        float posX;
        bool isMine;

        int sizeXSheet;
        int sizeYSheet;
        int posXSheet;
        int posYSheet;
        
        int frameCountWalk;
        int frameCountAttack;
        int* frameDurationWalk;
        int* frameDurationAttack;

        bool animationState[3];
        void verifyUniqueAnimation(int);

        int frameTravel;
        int frameCounter;

        image characterSheet;
    public:
        character(int auxID, bool propery) :isMine(propery), ID(auxID)
        {
            string nameCharacter = to_string(ID);
            if (!isMine)
                nameCharacter = "enemy/" + nameCharacter;
            nameCharacter = "characters/" + nameCharacter;
            characterSheet.setBitmap(nameCharacter, ".png");

            sizeXSheet = getAnimationFromDB(ID, "sizeXSheet");
            sizeYSheet = getAnimationFromDB(ID, "sizeYSheet");
            frameCountWalk = getAnimationFromDB(ID, "frameCountWalk");
            frameDurationWalk = getArrayAnimationFromDB(ID, "frameDurationWalk", frameCountWalk);
            frameCountAttack = getAnimationFromDB(ID, "frameCountAttack");
            frameDurationAttack = getArrayAnimationFromDB(ID, "frameDurationAttack", frameCountWalk);
            animationState[0] = false; animationState[1] = false; animationState[2] = false;
            frameTravel = 0;
            frameCounter = 1;
            
            posXSheet = 0;
            posYSheet = 0;
            posX = 0; 

        }
        ~character()
        {
            delete[] frameDurationWalk;
            delete[] frameDurationAttack;
        }
        void avanzar() { if (isMine) posX+=0.5; else { posX--; } }
        void generateCharacter(int state)
        {
            posYSheet = (state-1)*sizeYSheet;
            animationState[state - 1] = true;
            verifyUniqueAnimation(state);

            switch (state)
            {
                case 1:
                {
                    posXSheet = 0;
                    characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, 200);
                }break;
                case 2:
                {
                    if (frameTravel < frameCountWalk)
                    {
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, 200);
                        if (frameCounter == frameDurationWalk[frameTravel])
                        {
                            frameCounter = 1;
                            frameTravel++;
                            posXSheet += sizeXSheet;
                        }
                        else
                            frameCounter++;
                    }
                    if (frameTravel == frameCountWalk)
                    {
                        posXSheet = 0;
                        frameTravel = 0;
                        frameCounter = 1;
                    }
                    avanzar();
                }break;
                case 3:
                {         
                    if (frameTravel < frameCountAttack)
                    {
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, 200);
                        if (frameCounter == frameDurationAttack[frameTravel])
                        {
                            frameCounter = 1;
                            frameTravel++;
                            posXSheet += sizeXSheet;
                        }
                        else
                            frameCounter++;
                    }
                    if (frameTravel == frameCountAttack)
                    {
                        posXSheet = 0;
                        frameTravel = 0;
                        frameCounter = 1;
                    }           
                }break;
                
            }
            
        }
        //virtual void atacar() = 0
        //virtual void perderVida() = 0;
};

void character::verifyUniqueAnimation(int state)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (animationState[i])
        {
            count++;
        }
    }
    if (count >= 2)
    {
        animationState[0] = false; animationState[1] = false; animationState[2] = false;
        animationState[state - 1] = true;
        posXSheet = 0;
        frameTravel = 0;
        frameCounter = 1;
    }
}

