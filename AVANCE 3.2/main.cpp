#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "character.h"
#include "background.h"
#include "tower.h"
#include "button.h"
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
int x = 0;
int y = 0;
int main()
{

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT event;
	srand(time(NULL));
	al_init();
	
	display = al_create_display(1920, 1080);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	
	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_init_image_addon();
	vector<character>aliados;
	vector<character>enemies;
	tower torreAmiga(100, true, 1);
	tower torreEnemiga(100, false, 1);
	background fondo(2);
	bool running = true;
	int mousex = 0;
	int mousey = 0;
	al_start_timer(timer);

	
	while (running)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
		if (x < 50)
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (event.mouse.button & 1)
				{		
					aliados[x].reInitialize(1, true);
					x++;
				}
			}
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
			fondo.generateBG();
			torreAmiga.generateTower();
			torreEnemiga.generateTower();	
			if (y < 50)
				if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					enemies[y].reInitialize(1, false);
					y++;
				}
			for (int i = 0; i < x; i++)	
			{
				aliados[i].generateCharacter(enemies, y);			
			}
			for (int i = 0; i < y; i++)
				enemies[i].generateCharacter(aliados, x);
			al_flip_display();
		}
	}
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
}