#pragma once
#include <iostream>
#include <cstdlib> 
#include <string>
#include "conexion.cpp"
#include "image.h"

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
        character() { voidInitialize(); }
        character(int auxID, bool propery){reInitialize(auxID, propery);}
        int getID() { return ID; }
        int getPosX() { return posX; }
        int getHP() { return HP; }
        int getHitboxEnd() { return hitboXEnd; }
        void voidInitialize()
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
            frameCounter = 0;
            frameAttack = 0;

            posXSheet = -1000;
            posYSheet = 0;
            posX = 0;
            posY = 0;
            focusID = 0;
        }
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
            range = getDataIndicator<int>(ID, "rangeCh");
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
            frameDurationAttack = getArrayAnimationFromDB(ID, "frameDurationAttack", frameCountAttack); 
            hitboXOrigin = getAnimationFromDB(ID, "hitboXOrigin");
            hitboXEnd = getAnimationFromDB(ID, " hitboXEnd");
            animationState[0] = false; animationState[1] = false; animationState[2] = false;
            frameTravel = 0;
            frameCounter = 1;
            frameAttack = getAnimationFromDB(ID, "frameAttack");;

            posXSheet = 0;
            posYSheet = 0;
            posX = 150;
            if (!isMine) posX = 1770 - sizeXSheet;
            posY = 650 + rand() % (670 + 1 - 650);
            focusID = 0;          
        }
        ~character()
        {
            delete[] frameDurationWalk;
            delete[] frameDurationAttack;
        }
        void avanzar() { if (isMine) posX+=1; else { posX-=1; } }
        void generateCharacter(vector<character>enemies)
        {            
            if (ID <= 0)
                return;
            bool haveEnemy = false;
            if (isMine) 
            {      
                for (int i = 0; i < x; i++)
                {
                    if (posX + hitboXEnd + range <= enemies[i].getPosX() + 100 && posX + hitboXEnd + range >= enemies[i].getPosX())
                    {
                        haveEnemy = true;
                        focusID = i;
                        break;
                    }
                }              
            }
            else
            {
                for (int i = 0; i < x; i++)
                {
                    if (posX + hitboXOrigin - range >= enemies[i].getPosX() + enemies[i].getHitboxEnd() - 100 && posX + hitboXOrigin - range <= enemies[i].getPosX()+ enemies[i].getHitboxEnd())
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
                    enemies[focusID].modifyHP(damage);
                    if (enemies[focusID].getHP() <= 0)
                    {
                        enemies[focusID].voidInitialize();
                        focusID = 0;
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
        void modifyHP(int x)
        {
            HP -= x;
            if (isMine)cout << "MI VIDA: ";
            else { cout << "VIDA ENEMIGA: "; }
            cout << HP << endl;
        }
        
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