#pragma once
#include <iostream>
#include "data.cpp"
#include "image.h"
#include <Windows.h>
#include <WinUser.h>
using namespace std;

class button
{
	protected:
		int x, y;
		int buttonWidth, buttonHeight;
		void (*buttonVoid)(void);
		void (*buttonGenerate)(int, vector<character*>&, int&, bool,background&);
		image buttonIdle;
		image buttonPress;
		bool canTouch;
		bool gonnaPress;
		bool activate;
		int frameCounter;
		int frameLimit;
	public:
		button(string name, int ax, int ay, void (*btn)(void),int fL) :x(ax), y(ay), frameLimit(fL)
		{
			string tempName = "buttons/" + name + "_iddle";
			buttonIdle.setBitmap(tempName, ".png");
			tempName = "buttons/" + name + "_press";
			buttonPress.setBitmap(tempName, ".png");
			buttonWidth = buttonIdle.getWidth();
			buttonHeight = buttonIdle.getHeight();
			buttonGenerate = NULL;
			buttonVoid = btn;
			canTouch = false;
			gonnaPress = false;
			activate = true;
			frameCounter = 0;
		}
		button(string name, int ax, int ay, void (*btn)(int, vector<character*>&, int&, bool, background&), int fL) :x(ax), y(ay), frameLimit(fL)
		{
			string tempName = "buttons/" + name + "_iddle";
			buttonIdle.setBitmap(tempName, ".png");
			tempName = "buttons/" + name + "_press";
			buttonPress.setBitmap(tempName, ".png");
			buttonWidth = buttonIdle.getWidth();
			buttonHeight = buttonIdle.getHeight();
			buttonGenerate = btn;
			canTouch = false;
			gonnaPress = false;
			frameCounter = 0;
			activate = true;
			buttonVoid = NULL;
		}
		int getX() { return x; }
		int getY() { return y; }
		int getButtonWidth() { return buttonWidth; }
		int getButtonHeight() { return buttonHeight; }
		void rechargeButton(ALLEGRO_EVENT event)
		{	
			POINT mouse;
			GetCursorPos(&mouse);
			if(activate)
			{
				if (mouse.x > x && mouse.x < x + buttonWidth && mouse.y>y && mouse.y < y + buttonHeight)
				{
					gonnaPress = true;
					if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
						if (event.mouse.button & 1)
							canTouch = true;
				}
				else
					gonnaPress = false;
			}
			else
			{
				gonnaPress = false;
				dataIntialize();
			}

		}
		void generateBtn()
		{
			buttonIdle.generateImage(x, y);
			if (canTouch)
			{
				canTouch = false;
				buttonVoid();
			}
				
		}
		void generateBtn(int ID, vector<character*>& team, int& quantity, bool isMine, background& fontMoney)
		{		
			if (activate)
			{
				if (gonnaPress)
					buttonPress.generateImage(x, y);				
				else
					buttonIdle.generateImage(x, y);
				if (frameCounter == 0)
				{
					if (canTouch)
					{
						canTouch = false;
						activate = false;
						buttonGenerate(ID, team, quantity, isMine, fontMoney);
						frameCounter++;
					}
				}			
			}
			else
				buttonIdle.generateImage(x, y);
			if (frameCounter > 0)
			{
				canTouch = false;
				frameCounter++;
				if (frameCounter == frameLimit)
				{
					frameCounter = 0;
					activate = true;
				}
			}
		}
};
