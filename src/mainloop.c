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

/* Main Loop, event dispatcher */

#include "main.h"

int continue_loop = 1;

/* This is the mainloop, acts like an event dispatcher */
void mainLoop(void) {
	ALLEGRO_EVENT ev;

	void (*input_fncn) (ALLEGRO_EVENT) = NULL;
	void (*update_fncn) (void) = NULL;

	while (al_wait_for_event(event_queue, &ev), continue_loop) { /* triggered very often due to the Timer event */

		if(ev.type == ALLEGRO_EVENT_TIMER) { /* time to refresh our screen */
			update_fncn = (void (*)(void)) get_current_update_function(NULL);
			if (update_fncn) update_fncn();

		} else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { /* byebye */
			break; /* fast quit-game */

		} else if (	ev.type == ALLEGRO_EVENT_KEY_DOWN ||             /* keyboard key pressed */
					ev.type == ALLEGRO_EVENT_KEY_UP ){               /* key released */

			input_fncn = (void (*)(ALLEGRO_EVENT)) get_current_input_function(NULL);
			if (input_fncn) input_fncn(ev);
		}
	}
}

void * get_current_input_function(void (*param) (ALLEGRO_EVENT)) {
	static void (*fncn) (ALLEGRO_EVENT) = NULL;
	if (param) {
		fncn = param;
	}
	return fncn;
}
void * get_current_update_function(void (*param) (void)) {
	static void (*fncn) (void) = NULL;
	if (param) {
		fncn = param;
	}
	return fncn;
}
