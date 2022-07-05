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
		int numTower;
		image towerBitmap;
	public:
		tower(int auxHealth, bool propery, int num) :health(auxHealth),isMine(propery),numTower(num)
		{
			string nameBG = to_string(numTower);
			if (isMine)
				nameBG = "mine_" + nameBG;
			else
				nameBG = "enemy_" + nameBG;
			nameBG = "tower/" + nameBG;
			towerBitmap.setBitmap(nameBG, ".png");
		}
		tower():health(999999),isMine(true),numTower(0) {}
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
			towerBitmap.generateImage(x,150);
		}
};