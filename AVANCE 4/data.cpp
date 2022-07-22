#pragma once
#include <iostream>
using namespace std;
struct dataBase
{
    int ID;

    int HP;
    int range;
    int damage;
    float attackSpeed;
    float speedMovement;
    bool areaDamage;
    int price;

    int sizeXSheet;
    int sizeYSheet;
    int hitboXOrigin;
    int hitboXEnd;

    int frameCountWalk;
    int frameCountAttack;
    int* frameDurationWalk;
    int* frameDurationAttack;
    int frameAttack;
}characterArray[2];
void dataIntialize()
{   
    characterArray[0] = { 0, 0,0,0,0,0,false,0,0,0,0,0,0,0,NULL,NULL,0 },
    characterArray[1] = { 1, 100,100,20,1.5,3,false,10,256,256,35,235,4,5,new int[4],new int[5],3 };
    characterArray[1].frameDurationWalk[0] = 8; characterArray[1].frameDurationWalk[1] = 8; characterArray[1].frameDurationWalk[2] = 8; characterArray[1].frameDurationWalk[3] = 8;
    characterArray[1].frameDurationAttack[0] = 2; characterArray[1].frameDurationAttack[1] = 20; characterArray[1].frameDurationAttack[2] = 2; characterArray[1].frameDurationAttack[3] = 2; characterArray[1].frameDurationAttack[4] = 100;
}
int getDB(int ID, string name)
{
        if(name=="HP") { return characterArray[ID].HP; }
        if(name=="range"){return characterArray[ID].range; }
        if(name=="damage") { return characterArray[ID].damage; }
        if(name=="range") { return characterArray[ID].range; }
        if(name=="price") { return characterArray[ID].price; }
        if(name=="sizeXSheet") { return characterArray[ID].sizeXSheet; }
        if(name=="sizeYSheet") { return characterArray[ID].sizeYSheet; }
        if(name=="hitboXOrigin") { return characterArray[ID].hitboXOrigin; }
        if(name=="hitboXEnd") { return characterArray[ID].hitboXEnd; }
        if(name=="frameCountWalk") { return characterArray[ID].frameCountWalk; }
        if(name=="frameCountAttack") { return characterArray[ID].frameCountAttack; }
        
        if(name=="frameAttack") { return characterArray[ID].frameAttack; }   
}
bool getDB(int ID){ return characterArray[ID].areaDamage;}
float getDB(int ID, string name, bool temp)
{
    if(temp)
    {
        if (name == "attackSpeed") { return characterArray[ID].attackSpeed; }
        if (name == "speedMovement") { return characterArray[ID].speedMovement; }
    }
}
int* getDB(int ID, int walkAttack)
{
    if (walkAttack == 0) { return characterArray[ID].frameDurationWalk; }
    if (walkAttack == 1) { return characterArray[ID].frameDurationAttack; }
}
void deleteData()
{
    for (int i = 1; i <= 1; i++)
    {
        delete[] characterArray[i].frameDurationWalk;
        delete[] characterArray[i].frameDurationAttack;
    }
}

