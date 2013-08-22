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

/* Main header */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>

/* remove posix-related warnings on Windows */
#if defined(WIN32) || defined(__WIN32__) || defined(_WIN32)
	#pragma warning(disable : 4996)
#endif

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_memfile.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include "dataload.h"
#include "gmath.h"

/* Project Configuration */ /* FIXME */
#define APP_NAME "Alleg Codebase"
#define RESOURCES_DIR "data"
#define FPS 30
#define SCREEN_W 1080
#define SCREEN_H 720

/* FLAGS for loaded_mods */
#define L_DISPLAY  (0x01 << 0) /* Display created */
#define L_INPUT_K  (0x01 << 1) /* Keyboard available */
#define L_INPUT_M  (0x01 << 2) /* mouse available */
#define L_EV_QUEUE (0x01 << 3) /* Event Queue created */
#define L_BITMAP_F (0x01 << 4) /* Bitmap files formats loaded */
#define L_AUDIO_BG (0x01 << 5) /* Audio subsystem loaded */
#define L_TIMER_EV (0x01 << 6) /* Timer Event Source */
#define L_PRIM_ADD (0x01 << 7) /* Primitive Addon Loaded */
#define L_CON_FONT (0x01 << 8) /* Console font loaded */
#define L_INPUT_J  (0x01 << 9) /* Joystick available */

/* Some globals */
uint32_t loaded_mods;				/* To know which part of allegro and the codebase is loaded */
ALLEGRO_DISPLAY *display;			/* for drawing purposes */
ALLEGRO_EVENT_QUEUE *event_queue;	/* mainloop's event queue */
ALLEGRO_FONT *console_font;			/* console-style font (use it for debugging, ...) */

/* returns current input/update functions, changeable with a not NULL arg */
void * get_current_input_function(void (*fncn) (ALLEGRO_EVENT));
void * get_current_update_function(void (*fncn) (void));

/* start the game's mainloop / event dispatcher */
void mainLoop(void);

/* Prints an error in a gui message box */
#define show_error(str) al_show_native_message_box(NULL,"Error", "An unexpected error occurred", str, NULL, ALLEGRO_MESSAGEBOX_ERROR)
#define fatal_error(msg) {show_error(msg); goto cleanup;}

#endif /* MAIN_H_ */
