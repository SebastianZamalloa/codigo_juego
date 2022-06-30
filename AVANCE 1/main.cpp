#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "background.h"
#include <iostream>
using namespace std;

int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;

	al_init();
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
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
	image prueba2("base",".png");
	image gato("image(2)", ".jpg");
	ALLEGRO_BITMAP* bases;
	ALLEGRO_BITMAP* bitmaps;
	ALLEGRO_BITMAP* gatoo;
	gatoo = gato.getBitmap();
	bitmaps = prueba.getBG();
	bases = prueba2.getBitmap();
	assert(bitmaps != NULL);

	float x = 0, y = 0;
	bool running = true, appear = false;
	int width = al_get_display_width(display);
	int height = al_get_display_height(display);
	al_start_timer(timer);
	while (running)
	{
		ALLEGRO_EVENT event;
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
					appear = !appear;
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
			al_draw_bitmap(bitmaps, 0, 0, 0);
			al_draw_bitmap(bases, 0, 0, 0);
			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && appear == false)
				appear = true;
			if (appear == true)
				al_draw_bitmap(gatoo, x, y, 0);
			al_flip_display();
		}

		if (x > width) x = -al_get_bitmap_width(gatoo);
	}
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_bitmap(bitmaps);
}