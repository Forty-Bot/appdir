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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define test_fallback(f) do { \
	char *f##_name = f("name", "name"); \
	char *f##_NULL = f("name", NULL); \
	assert_streq(f##_name, f##_NULL); \
	free(f##_name); \
	free(f##_NULL); \
} while (0)

#define test_fallback_list(f) do { \
	char **f##_name = f("name", "name"); \
	char **f##_NULL = f("name", NULL); \
	assert_strlisteq(f##_name, f##_NULL); \
	appdir_list_put(f##_name); \
	appdir_list_put(f##_NULL); \
} while (0)

char *test_fallbacks()
{
	struct appdir *ad_name, *ad_NULL;

	test_fallback(appdir_data);
	test_fallback_list(appdir_data_dirs);
	test_fallback(appdir_cfg);
	test_fallback_list(appdir_cfg_dirs);
	test_fallback(appdir_cache);
	test_fallback(appdir_log);

	ad_name = appdir_get("name", "name");
	ad_NULL = appdir_get("name", NULL);
	assert_strlisteq(ad_name->data_dirs, ad_NULL->data_dirs);
	assert_strlisteq(ad_name->cfg_dirs, ad_NULL->cfg_dirs);
	assert_streq(ad_name->cache, ad_NULL->cache);
	assert_streq(ad_name->log, ad_NULL->log);
	appdir_put(ad_name);
	appdir_put(ad_NULL);

	return 0;
}


int main()
{
	char *ret = test_fallbacks();
	if (ret)
		fprintf(stderr, "%s\n", ret);

	return !!ret;
}
