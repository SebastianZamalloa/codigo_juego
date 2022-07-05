#pragma once
#include <iostream>
#include "image.h"
#include <string>
using namespace std;

class background
{
protected:
	int numBG;
	image imageBG;
public:
	background(int numTemp):numBG(numTemp)
	{
		string nameBG = to_string(numBG);
		nameBG = "background/" + nameBG;
		imageBG.setBitmap(nameBG,".png");
	}
	~background(){}
	ALLEGRO_BITMAP* getBG() { return imageBG.getBitmap(); }
	void generateBG(){imageBG.generateImage(0,0);}
};