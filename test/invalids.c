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

#define test_invalid(f) do { \
	void *dir; \
	errno = 0; \
	dir = appdir_data(NULL, NULL); \
	assert_eq(dir, NULL); \
	assert_eq(errno, EINVAL); \
} while (0)

char *test_invalids()
{
	test_invalid(appdir_data);
	test_invalid(appdir_data_dirs);
	test_invalid(appdir_cfg);
	test_invalid(appdir_cfg_dirs);
	test_invalid(appdir_cache);
	test_invalid(appdir_log);
	test_invalid(appdir_get);

	return 0;
}

int main()
{
	char *ret = test_invalids();
	if (ret)
		fprintf(stderr, "%s\n", ret);

	return !!ret;
}
