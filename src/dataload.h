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

/* Loads resources from disk */

#ifndef _DATALOAD_H_
#define _DATALOAD_H_

/* is this file exists in the `data` dir ? */
int resource_exist(const char *filename);

/* Open any file from the `data` dir by it's name */
ALLEGRO_FILE * open_resource(const char *filename, const char *mode);

/* Load a bitmap/sound from the `data` dir by it's name */
ALLEGRO_BITMAP * get_resource_image(const char *filename);
ALLEGRO_SAMPLE * get_resource_sound(const char *filename);

#endif
