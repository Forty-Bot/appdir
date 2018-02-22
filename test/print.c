/*
 * Copyright (C) 2018 Sean Anderson
 *
 * This file is part of c-appdir.
 *
 * c-appdir is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * c-appdir is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with c-appdir. If not, see <http://www.gnu.org/licenses/>.
 */

#include "appdir.h"

#include <stdio.h>
#include <stdlib.h>

#define print(x) do { \
	if (x) \
		printf("%s\n", (x)); \
	else \
		printf("NULL\n"); \
} while (0)

#define print_func(f) do { \
	char *dir = appdir_##f("name", "author"); \
	printf(#f " = "); \
	print(dir); \
	free(dir); \
} while (0)

#define print_list(name, xs) do { \
	size_t i; \
	for (i = 0; xs[i]; i++) { \
		printf(name "[%lu] = ", (unsigned long)i); \
		print(xs[i]); \
	} \
} while (0)

#define print_list_func(f) do { \
	char **dirs = appdir_##f("name", "author"); \
	if (dirs) \
		print_list(#f, dirs); \
	else \
		printf(#f " = NULL\n"); \
	appdir_list_put(dirs); \
} while (0)

int main() {
	struct appdir *ad;

	print_func(data);
	print_list_func(data_dirs);
	print_func(cfg);
	print_list_func(cfg_dirs);
	print_func(cache);
	print_func(log);
	
	ad = appdir_get("name", "author");
	print_list("appdir()->data_dirs", ad->data_dirs);
	print_list("appdir()->cfg_dirs", ad->cfg_dirs);
	printf("appdir()->cache = ");
	print(ad->cache);
	printf("appdir()->log = ");
	print(ad->log);
	appdir_put(ad);

	return 0;
}
