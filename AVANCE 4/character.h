#pragma once
#include <iostream>
#include <cstdlib> 
#include <string>
#include "image.h"
#include <vector>
#include "data.cpp"
using namespace std;
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
        character(int auxID, bool propery){reInitialize(auxID, propery);}
        int getID() { return ID; }
        int getPosX() { return posX; }
        int getHP() { return HP; }
        int getHitboxEnd() { return hitboXEnd; }        
        void reInitialize(int auxID, bool propery)
        {
            ID = auxID;
            isMine = propery;
            string nameCharacter = to_string(ID);
            if (!isMine)
                nameCharacter = "enemy/" + nameCharacter;
            nameCharacter = "characters/" + nameCharacter;
            characterSheet.setBitmap(nameCharacter, ".png");
            
            HP = getDB(ID, "HP");
            range = getDB(ID, "range");            
            damage = getDB(ID, "damage");

            attackSpeed = getDB(ID, "attackSpeed",true);
            speedMovement = getDB(ID, "speedMovement",true);

            areaDamage = getDB(ID);
            price = getDB(ID, "price");
            
            sizeXSheet = getDB(ID, "sizeXSheet");
            sizeYSheet = getDB(ID, "sizeYSheet");
            frameCountWalk = getDB(ID, "frameCountWalk");
            frameDurationWalk = getDB(ID, 0);
            frameCountAttack = getDB(ID, "frameCountAttack");
            frameDurationAttack = getDB(ID, 1); 
            hitboXOrigin = getDB(ID, "hitboXOrigin");
            hitboXEnd = getDB(ID, "hitboXEnd");
            animationState[0] = false; animationState[1] = false; animationState[2] = false;
            frameTravel = 0;
            frameCounter = 1;
            frameAttack = getDB(ID, "frameAttack");

            posXSheet = 0;
            posYSheet = 0;
            posX = 150;
            if (!isMine) posX = 1770 - sizeXSheet;
            posY = 650 + rand() % (670 + 1 - 650);
            focusID = -1;  
        }
        ~character(){}
        void avanzar() { if (isMine) posX+=1*speedMovement; else { posX-=1* speedMovement; } }
        void generateCharacter(vector<character*>&enemies)
        {         
            bool haveEnemy = false;
            if(focusID>=0)
                if (enemies[focusID] == NULL)
                    focusID = -1;
            if (isMine) 
            {      
                for (int i = 0; i < enemies.size(); i++)
                {
                    if(enemies[i] != NULL)
                        if (posX + hitboXEnd + range <= enemies[i]->getPosX() + 100 && posX + hitboXEnd + range >= enemies[i]->getPosX())
                        {
                            haveEnemy = true;
                            focusID = i;
                            break;
                        }
                }              
            }
            else
            {
                for (int i = 0; i < enemies.size(); i++)
                {
                    if (enemies[i] != NULL)
                        if (posX + hitboXOrigin - range >= enemies[i]->getPosX() + enemies[i]->getHitboxEnd() - 100 && posX + hitboXOrigin - range <= enemies[i]->getPosX()+ enemies[i]->getHitboxEnd())
                        {
                            haveEnemy = true;
                            focusID = i;
                            break;
                        }
                }             
            }

            if (haveEnemy)
            {
                animateCharacter(3);        
                if (frameTravel == frameAttack - 1 && frameCounter == 1)
                {
                    enemies[focusID]->modifyHP(damage);
                    
                    if (enemies[focusID]->getHP() <= 0)
                    {
                        delete enemies[focusID];
                        enemies[focusID] = NULL;
                        focusID = -1;
                    }
                }                
            }
            else if (animationState[2])
            {
                animateCharacter(3);
            }
            else
                animateCharacter(2); 

        }
        void modifyHP(int x){HP -= x;}
        
        void animateCharacter(int state) //linea de tiempo
        {        
            int postempY = posY - sizeYSheet;
            posYSheet = (state-1)*sizeYSheet;
            animationState[state - 1] = true;
            verifyUniqueAnimation(state);

            switch (state)
            {
                case 1:
                {
                    posXSheet = 0;
                    characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, postempY);
                }break;
                case 2:
                {
                    if (frameTravel < frameCountWalk)
                    {
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, postempY);
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
                        characterSheet.generateImage(posXSheet, posYSheet, sizeXSheet, sizeYSheet, posX, postempY);
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
                        animationState[2] = false;
                    }                     
                }break;                
            }            
        }
};

void character::verifyUniqueAnimation(int state)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        if (animationState[i])
        {
            count++;
            if (count >= 2)
            {
                animationState[0] = false; animationState[1] = false; animationState[2] = false;
                animationState[state - 1] = true;
                posXSheet = 0;
                frameTravel = 0;
                frameCounter = 1;
                return;
            }
            
        }
    }
    
}
