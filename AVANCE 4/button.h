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
		void (*buttonGenerate)(int, vector<character*>&, int&, bool);
		image buttonImg;
		bool canTouch;
	public:
		button(string name, int ax, int ay, void (*btn)(void)) :x(ax), y(ay)
		{
			string tempName = "buttons/" + name;
			buttonImg.setBitmap(tempName, ".png");
			buttonWidth = buttonImg.getWidth();
			buttonHeight = buttonImg.getHeight();
			buttonGenerate = NULL;
			buttonVoid = btn;
			canTouch = false;
		}
		button(string name, int ax, int ay, void (*btn)(int, vector<character*>&, int&, bool)) :x(ax), y(ay)
		{
			string tempName = "buttons/" + name;
			buttonImg.setBitmap(tempName, ".png");
			buttonWidth = buttonImg.getWidth();
			buttonHeight = buttonImg.getHeight();
			buttonGenerate = btn;
			canTouch = false;
			buttonVoid = NULL;
		}
		int getX() { return x; }
		int getY() { return y; }
		int getButtonWidth() { return buttonWidth; }
		int getButtonHeight() { return buttonHeight; }
		void rechargeButton(ALLEGRO_EVENT event)
		{
			if (event.mouse.x > x && event.mouse.x < x + buttonWidth && event.mouse.y>y && event.mouse.y < y + buttonHeight)
			{
				if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					if (event.mouse.button & 1)
					{
						canTouch = true;
					}
				}
			}		
		}
		void generateBtn()
		{
			buttonImg.generateImage(x, y);
			if (canTouch)
			{
				canTouch = false;
				buttonVoid();
			}
				
		}
		void generateBtn(int ID, vector<character*>& team, int& quantity, bool isMine)
		{	
			buttonImg.generateImage(x, y);
			if (canTouch)
			{
				canTouch = false;
				buttonGenerate(ID,team,quantity,isMine);
			}					
		}
};
