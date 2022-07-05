#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "tower.h"
#include "background.h"
#include "Corto_alcance.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "me llegas avelino";
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT event;

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
	background prueba(1);
	Personajes* prueba2 = new CortoAlcance(true, 1);
	tower mine(100,true,1);
	tower enemy(100,false,1);
	Personajes* prueba3 = new CortoAlcance(false, 1);
	float x = 0, y = 0;
	bool running = true, appear = false;

	int width = al_get_display_width(display);
	int height = al_get_display_height(display);
	
	al_start_timer(timer);


	while (running)
	{
	
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = event.mouse.x;
			y = event.mouse.y;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (event.mouse.button & 1)
			{
				if (event.mouse.y >= height / 2)
				{
					appear = !appear;			// variabl band 
				}
			}
		}

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x += 10;
			else
				x += 1;
		

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
			prueba.generateBG();
			mine.generateTower();
			enemy.generateTower();
			prueba2->generateCharacter(100, 100);
			prueba3->generateCharacter(1420, 100);
			al_flip_display();
			
		}
	}
	delete prueba2, prueba3;
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
}