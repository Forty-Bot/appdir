/*
 * Copyright (C) 2018 Sean Anderson
 *
 * This file is part of appdir.
 *
 * appdir is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * appdir is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with appdir. If not, see <http://www.gnu.org/licenses/>.
 */

#include "internal.h"
#include "appdir.h"

#include <stdlib.h>
#include <string.h>

void appdir_list_put(char **dirs) {
	size_t i;

	if (!dirs)
		return;

	for (i = 0; dirs[i]; i++)
		free(dirs[i]);

	free(dirs);
}

void appdir_put(struct appdir *ad) {
	if (!ad)
		return;

	appdir_list_put(ad->data_dirs);
	appdir_list_put(ad->cfg_dirs);
	if (ad->cache)
		free(ad->cache);
	if (ad->log)
		free(ad->log);
	free(ad);
}

char *appdir_append(const char *a, const char *b) {
	char *ret;
	size_t a_len;
	size_t b_len;
	size_t ret_len;

	/* Don't clobber errno on error */
	if (!a || !b)
		return NULL;
	a_len = strlen(a);
	b_len = strlen(b);

	ret_len = a_len + b_len;
	ret = malloc(ret_len + 1);
	if (!ret)
		return NULL;

	memcpy(ret, a, a_len);
	memcpy(ret + a_len, b, b_len);
	ret[ret_len] = '\0';
	
	return ret;
}
