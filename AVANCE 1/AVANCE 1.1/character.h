#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
using namespace std;

class image
{
	protected:
		string archiveName;
		ALLEGRO_BITMAP* bitmap;
		float widthCh, heightCh;
	public:
		image(string nameTemp) :archiveName(nameTemp)
		{
			const char* name = archiveName.c_str();
			bitmap = al_load_bitmap(name);
			widthCh = al_get_bitmap_width(bitmap);
			heightCh = al_get_bitmap_height(bitmap);
		}
		~image(){}
		ALLEGRO_BITMAP* getBitmap() { return bitmap; }
		float getWidth() { return widthCh; }
		float getHeight() { return heightCh; }
};
