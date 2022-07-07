#pragma once
#include <iostream>
#include <string>
#include "image.h"
using namespace std;

class tower
{
protected:
	bool isMine;
	int health;
	int towerID;
	image towerBitmap;
public:
	tower(int auxHealth, bool propery, int num) :health(auxHealth), isMine(propery), towerID(num)
	{
		string nameTower = to_string(towerID);
		if (!isMine)
			nameTower = "enemy/" + nameTower;
		nameTower = "tower/" + nameTower;
		towerBitmap.setBitmap(nameTower, ".png");
	}
	tower() :health(999999), isMine(true), towerID(0) {}
	void setHealth(int auxHealth) { health = auxHealth; }
	void modifyHealth(int varHealth, bool damage)
	{
		if (damage) { health -= varHealth; }
		else { health += varHealth; }
	}
	void generateTower()
	{
		int x = 100;
		if (!isMine) { x = 1420; }
		towerBitmap.generateImage(x, 150);
	}
};