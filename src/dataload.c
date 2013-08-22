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

/* Load misc datas from disk */

#include "main.h"

/* if this file exists in the resource dir */
int resource_exist(const char *filename) {
	ALLEGRO_PATH *path;
	int res;
	
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, RESOURCES_DIR);
	al_set_path_filename(path, filename);

	res = al_filename_exists(al_path_cstr(path, '/'));
	al_destroy_path(path);
	return res;
}

/* opens a file in the resource dir */
ALLEGRO_FILE * open_resource(const char *filename, const char *mode) {
	ALLEGRO_PATH *path;
	ALLEGRO_FILE *file;
	
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, RESOURCES_DIR);
	al_set_path_filename(path, filename);
	
	file = al_fopen(al_path_cstr(path, '/'), mode);
	al_destroy_path(path);
	return file;
}

/* loads a bitmap in the resource dir */
ALLEGRO_BITMAP * get_resource_image(const char *filename) {
	ALLEGRO_PATH *path;
	ALLEGRO_BITMAP *image;
	
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, RESOURCES_DIR);
	al_set_path_filename(path, filename);
	
	image = al_load_bitmap(al_path_cstr(path, '/'));
	al_destroy_path(path);
	return image;
}
