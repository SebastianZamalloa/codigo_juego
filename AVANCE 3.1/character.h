#pragma once
#include <mysql.h>
#include <iostream>
#include "image.h"
#include <string>
#include "conexion.cpp"

class character
{
    protected:
        int ID;

        int HP;
        int range;
        int damage;
        float attackSpeed;
        float speedMovement;
        bool areaDamage;
        int price;

        float posX;
        float posY;
        bool isMine;

        int sizeXSheet;
        int sizeYSheet;
        int posXSheet;
        int posYSheet;

        int hitboXOrigin;
        int hitboXEnd;
        
        int frameCountWalk;
        int frameCountAttack;
        int* frameDurationWalk;
        int* frameDurationAttack;
        int frameAttack;
        int focusID;

        bool animationState[3];
        void verifyUniqueAnimation(int);

        int frameTravel;
        int frameCounter;

        image characterSheet;
    public:
        character()
        {
            ID = 0;
            isMine = true;    

            HP = 0;
            range = 0;
            damage = 0;
            attackSpeed = 0;
            speedMovement = 0;
            areaDamage = 0;
            price = 0;

            sizeXSheet = 0;
            sizeYSheet = 0;
            frameCountWalk = 0;
            frameDurationWalk = NULL;
            frameCountAttack = 0;
            frameDurationAttack = NULL;
            hitboXOrigin = 0;
            hitboXEnd = 0;
            animationState[0] = false; animationState[1] = false; animationState[2] = false;
            frameTravel = 0;
            frameCounter = 1;
            frameAttack = 1;

            posXSheet = 0;
            posYSheet = 0;
            posX = 150;
            posY = 0;
            focusID = 0;
        }
        character(int auxID, bool propery){reInitialize(auxID, propery);}
        int getID() { return ID; }
        int getPosX() { return posX; }
        void reInitialize(int auxID, bool propery)
        {
            ID = auxID;
            isMine = propery;
            string nameCharacter = to_string(ID);
            if (!isMine)
                nameCharacter = "enemy/" + nameCharacter;
            nameCharacter = "characters/" + nameCharacter;
            characterSheet.setBitmap(nameCharacter, ".png");
            
            HP = getDataIndicator<int>(ID, "HP");
            range = getDataIndicator<int>(ID, "range");
            damage = getDataIndicator<int>(ID, "damage");
            attackSpeed = getDataIndicator<float>(ID, "attackSpeed");
            speedMovement = getDataIndicator<float>(ID, "speedMovement");
            areaDamage = getDataIndicator<bool>(ID, "areaDamage");
            price = getDataIndicator<int>(ID, "price");
            
            sizeXSheet = getAnimationFromDB(ID, "sizeXSheet");
            sizeYSheet = getAnimationFromDB(ID, "sizeYSheet");
            frameCountWalk = getAnimationFromDB(ID, "frameCountWalk");
            frameDurationWalk = getArrayAnimationFromDB(ID, "frameDurationWalk", frameCountWalk);
            frameCountAttack = getAnimationFromDB(ID, "frameCountAttack");
            frameDurationAttack = getArrayAnimationFromDB(ID, "frameDurationAttack", frameCountWalk);
            hitboXOrigin = getAnimationFromDB(ID, "hitboXOrigin");
            hitboXEnd = getAnimationFromDB(ID, " hitboXEnd");
            animationState[0] = false; animationState[1] = false; animationState[2] = false;
            frameTravel = 0;
            frameCounter = 1;
            frameAttack = 1;

            posXSheet = 0;
            posYSheet = 0;
            posX = 150;
            if (!isMine) posX = 1770 - sizeXSheet;
            posY = 0;
            focusID = 0;
            cout << range << endl;
        }
        ~character()
        {
            delete[] frameDurationWalk;
            delete[] frameDurationAttack;
        }
        void avanzar() { if (isMine) posX+=3; else { posX--; } }
        void generateCharacter(character enemies[],int x)
        {
            bool haveEnemy = false;            
            for (int i = 0; i < x; i++)
            {
                if (posX + hitboXEnd + range <= enemies[i].getPosX()+50 && posX + hitboXEnd + range >= enemies[i].getPosX())
                {
                    haveEnemy = true;
                    focusID = i;
                    break;
                }
            }
            if (haveEnemy)
            {
                animateCharacter(3);  
                enemies[focusID].modifyHP(damage);
            }
            else
                animateCharacter(2);

        }
        void modifyHP(int x)
        {
            HP -= x;
            cout << HP<<" ";
        }
        
        void animateCharacter(int state)
        {
            posY = 650 - sizeYSheet;
            posYSheet = (state-1)*sizeYSheet;
            animationState[state - 1] = true;
            verifyUniqueAnimation(state);

            switch (state)
            {
                case 1:
                {
                    posXSheet = 0;
                    characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, posY);
                }break;
                case 2:
                {
                    if (frameTravel < frameCountWalk)
                    {
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, posY);
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
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, posY);
                        if (frameCounter == frameDurationAttack[frameTravel])
                        {
                            frameCounter = 1;
                            frameTravel++;
                            posXSheet += sizeXSheet;
                        }
                        if (frameTravel == frameAttack - 1)
                        {
                            
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
        //virtual void atacar() = 0;

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