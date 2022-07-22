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
void generateCharacter(int ID, vector<character*>& team, int &quantity, bool isMine)
{
	if (quantity < 50)
	{
		team.push_back(NULL);
		team[quantity] = new character(ID, isMine);
		quantity++;
	}
	if (quantity == 50)
	{
		for (int i = 0; i < 50; i++)
		{
			if (team[i] == NULL)
			{
				team[i] = new character(ID, isMine);
				return;
			}
		}
	}
	cout << quantity << endl;
}
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_EVENT event;
	srand(time(NULL));
	al_init();
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	display = al_create_display(1920, 1080);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	
	//al_set_window_position(display, 0, 0);
	
	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_init_image_addon();
	vector<character*>aliados;
	vector<character*>enemies;
	dataIntialize();
	tower torreAmiga(100, true, 1);
	tower torreEnemiga(100, false, 1);
	background fondo(2);
	button boton("prueba", 100, 100, generateCharacter,120);
	button boton2("prueba", 1500, 100, generateCharacter, 120);
	bool running = true;
	int mousex = 0;
	int mousey = 0;
	al_start_timer(timer);


	while (running)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
		boton.rechargeButton(event);
		boton2.rechargeButton(event);
		x = aliados.size();
		y = enemies.size();

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
			fondo.generateBG();
			torreAmiga.generateTower();
			torreEnemiga.generateTower();
			boton.generateBtn(1, aliados, x, true);
			boton2.generateBtn(1, enemies, y, false);
			for (int i = 0; i < x; i++)
			{
				if (aliados[i] != NULL)				
					aliados[i]->generateCharacter(enemies);
			}
			for (int i = 0; i < y; i++)
			{
				if (enemies[i] != NULL)
					enemies[i]->generateCharacter(aliados);
			}
			al_flip_display();
		}
	}
	deleteData();
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
}
