#pragma once
#include <iostream>
#include "image.h"

using namespace std;

class button
{
	protected:
		int x, y;
		int buttonWidth, buttonHeight;
		void (*buttonVoid)(void);
		void (*buttonGenerate)(int);
		image buttonImg;
	public:
		button(string name, int ax, int ay, void (*btn)(void)) :x(ax), y(ay)
		{
			string tempName = "buttons/" + name;
			buttonImg.setBitmap(tempName, ".png");
			buttonWidth = buttonImg.getWidth();
			buttonHeight = buttonImg.getHeight();
			buttonGenerate = NULL;
			buttonVoid = btn;
		}
		button(string name, int ax, int ay, void (*btn)(int)) :x(ax), y(ay)
		{
			buttonImg.setBitmap(name, ".png");
			buttonWidth = buttonImg.getWidth();
			buttonHeight = buttonImg.getHeight();
			buttonGenerate = btn;
			buttonVoid = NULL;
		}
		int getX() { return x; }
		int getY() { return y; }
		int getButtonWidth() { return buttonWidth; }
		int getButtonHeight() { return buttonHeight; }
		void generateBtn(bool confirm)
		{
			buttonImg.generateImage(x, y);
			if (confirm)
				buttonVoid();
		}
		void generateBtn(int ID, bool confirm)
		{	
			buttonImg.generateImage(x, y);
			if (confirm)
				buttonGenerate(ID);			
		}
};
