#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "character.h"
#include "background.h"
#include "tower.h"
#include <iostream>
using namespace std;
int main()
{

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

	character* aliados = new character[50];
	aliados[0].reInitialize(1, true);
	tower torreAmiga(100, true, 1);
	tower torreEnemiga(100, false, 1);
	character *enemigos= new character[50];
	enemigos[0].reInitialize(1, false);
	background fondo(1);

	float x = 1, y = 0;
	bool running = true, appear = false;

	int width = al_get_display_width(display);
	int height = al_get_display_height(display);

	al_start_timer(timer);

	
	while (running)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (x == 1)x = 2;
			else if (x == 2)x = 1;
			if (x == 3)x = 2;
		}
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			x = 3;
		}
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
			fondo.generateBG();
			torreAmiga.generateTower();
			torreEnemiga.generateTower();
			aliados[0].generateCharacter(enemigos,1);
			enemigos[0].animateCharacter(x);
			al_flip_display();

		}
	}
	delete[]enemigos;
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
}