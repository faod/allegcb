/*
    Allegro CodeBase
    Copyright (C) 2012 Bayle Jonathan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Alleg and Game init */

#include "main.h"

ALLEGRO_FONT *console_font = NULL;			/* Default console font */
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
uint32_t loaded_mods = 0;

static ALLEGRO_TIMER *timer = NULL;

static uint32_t init_alleg(void);
static void uninstall_alleg(uint32_t loaded_mods);
static void register_event_sources(void);

int main(int argc, char **argv) {
	if (loaded_mods = init_alleg(), !loaded_mods) return -1;

	register_event_sources();

	al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_PRECISION);
	get_current_update_function(NULL);
	get_current_input_function(NULL);

	al_start_timer(timer);
	mainLoop();
	al_stop_timer(timer);

	uninstall_alleg(loaded_mods);
	
	return 0;
}

static void register_event_sources(void) {
	/* ALLEGRO_EVENT_DISPLAY_*** */
	al_register_event_source(event_queue, al_get_display_event_source(display));
	/* ALLEGRO_EVENT_JOYSTICK_*** */
	/*al_register_event_source(event_queue, al_get_joystick_event_source());*/
	/* ALLEGRO_EVENT_KEY_*** */
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	/* ALLEGRO_EVENT_TIMER */
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

static uint32_t init_alleg(void) {
	if(!al_init()) fatal_error("failed to initialize allegro!");

	al_set_app_name(APP_NAME);
	al_set_org_name(APP_NAME);

	if(display = al_create_display(SCREEN_W, SCREEN_H), !display) fatal_error("failed to create display!");
	loaded_mods |= L_DISPLAY;

	if(!al_install_keyboard()) fatal_error("failed to initialize the keyboard!");
	loaded_mods |= L_INPUT_K;

	if(!al_install_mouse()) fatal_error("failed to initialize the mouse!");
	loaded_mods |= L_INPUT_M;

	/*if(!al_install_joystick()) show_error("failed to initialize the joystick!");
	loaded_mods |= L_INPUT_J;*/

	if(event_queue = al_create_event_queue(), !event_queue) fatal_error("failed to create event_queue!");
	loaded_mods |= L_EV_QUEUE;

	if (!al_init_image_addon()) fatal_error("failed to initialise image support!");
	loaded_mods |= L_BITMAP_F;

	if (!al_install_audio() || !al_init_acodec_addon()) show_error("failed to initialise audio subsystem!");
	loaded_mods |= L_AUDIO_BG;

	if (timer = al_create_timer(1.0/FPS), !timer) fatal_error("failed to initialise the timer!");
	loaded_mods |= L_TIMER_EV;

	if (!al_init_primitives_addon()) fatal_error("failed to initialise primitives!");
	loaded_mods |= L_PRIM_ADD;

	al_init_font_addon();
	if (!(console_font = al_create_builtin_font())) show_error("failed to initialise console font!");
	else loaded_mods |= L_CON_FONT;

	return 1;

	/* in case of error this code is run */
cleanup:
	uninstall_alleg(loaded_mods);
	return 0;
}

static void uninstall_alleg(uint32_t status) {
	if (status & L_CON_FONT) al_destroy_font(console_font);
	if (status & L_DISPLAY ) al_destroy_display(display);
	if (status & L_INPUT_K ) al_uninstall_keyboard();
	if (status & L_INPUT_M ) al_uninstall_mouse();
	if (status & L_INPUT_J ) al_uninstall_joystick();
	if (status & L_EV_QUEUE) al_destroy_event_queue(event_queue);
	if (status & L_BITMAP_F) al_shutdown_image_addon();
	if (status & L_AUDIO_BG) al_uninstall_audio();
	if (status & L_TIMER_EV) al_destroy_timer(timer);
}
