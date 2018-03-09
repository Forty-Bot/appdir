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

#include "appdir.h"
#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test basic equalities and equivalencies */
char *test_equiv() {
	char *dir;
	char **dirs;
	struct appdir *ad;
	
	ad = appdir_get("name", "author");
	assert_nonnull(ad);

	dirs = appdir_data_dirs("name", "author");
	assert_strlisteq(ad->data_dirs, dirs);
	appdir_list_put(dirs);

	dirs = appdir_cfg_dirs("name", "author");
	assert_strlisteq(ad->cfg_dirs, dirs);
	appdir_list_put(dirs);
	
	assert_nonnull(ad->cache);
	dir = appdir_cache("name", "author");
	assert_nonnull(dir);
	assert_streq(ad->cache, dir);
	free(dir);

	assert_nonnull(ad->log);
	dir = appdir_log("name", "author");
	assert_nonnull(dir);
	assert_streq(ad->log, dir);
	free(dir);

	appdir_put(ad);
	return 0;
}

int main() {
	char *ret = test_equiv();
	if (ret)
		fprintf(stderr, "%s\n", ret);

	return !!ret;
}
