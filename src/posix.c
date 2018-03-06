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
#include "internal.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <basedir.h>

#define DIR_SEP '/'

static char *appdir_home(const char *name,
			 const char *xdg_home(xdgHandle *), xdgHandle *h) {
	const char *home;
	char *ret;
	char *p;
	size_t name_len;
	size_t ret_len;
	size_t home_len;

	if (!name) {
		errno = EINVAL;
		return NULL;
	}
	name_len = strlen(name);
	
	home = xdg_home(h);
	if (!home)
		return NULL;
	home_len = strlen(home);
	
	/* +1 for the separator */
	ret_len = home_len + 1 + name_len;
	ret = malloc(ret_len + 1);
	if (!ret)
		return NULL;
	p = ret;

	memcpy(p, home, home_len);
	p += home_len;

	*p++ = DIR_SEP;

	memcpy(p, name, name_len);
	p += name_len;

	*p = '\0';

	return ret;
}

char *appdir_data(const char *name, const char *author) {
	UNUSED(author);
	return appdir_home(name, xdgDataHome, NULL);
}

static char **appdir_dirs(const char *name,
			    const char *const *xdg_dirs(xdgHandle *),
			    xdgHandle *h) {
	const char *const *dirs;
	char **ret;
	size_t dirs_len = 0;
	size_t i;
	size_t name_len;
	
	if (!name) {
		errno = EINVAL;
		return NULL;
	}
	name_len = strlen(name);

	dirs = xdg_dirs(h);
	if (!dirs)
		return NULL;
	while (dirs[dirs_len++]);
	dirs_len--;

	ret = malloc(sizeof(*ret) * (dirs_len + 1));
	if (!ret)
		return NULL;
	for (i = 0; i < dirs_len; i++) {
		char *p;
		size_t dir_len = strlen(dirs[i]);
		size_t ret_len = dir_len + 1 + name_len;

		ret[i] = malloc(ret_len + 1);
		if (!ret[i]) {
			size_t j;
			for (j = 0; j < i; j++)
				free(ret[j]);
			free(ret);
			return NULL;
		}
		p = ret[i];

		memcpy(p, dirs[i], dir_len);
		p += dir_len;

		*p++ = DIR_SEP;

		memcpy(p, name, name_len);
		p += name_len;

		*p = '\0';
	}
	ret[dirs_len] = NULL;

	return ret;
}

char **appdir_data_dirs(const char *name, const char *author) {
	UNUSED(author);
	return appdir_dirs(name, xdgSearchableDataDirectories, NULL);
}

char *appdir_cfg(const char *name, const char *author) {
	UNUSED(author);
	return appdir_home(name, xdgConfigHome, NULL);
}

char **appdir_cfg_dirs(const char *name, const char *author) {
	UNUSED(author);
	return appdir_dirs(name, xdgSearchableConfigDirectories, NULL);
}

char *appdir_cache(const char *name, const char *author) {
	UNUSED(author);
	return appdir_home(name, xdgCacheHome, NULL);
}

char *appdir_log(const char *name, const char *author) {
	char *ret;
	char *cache = appdir_home(name, xdgCacheHome, NULL);
	UNUSED(author);

	if (!cache)
		return NULL;
	ret = appdir_append(cache, "/log");
	free(cache);
	return ret;
}

struct appdir *appdir_get(const char *name, const char *author) {
	struct appdir *ret;
	xdgHandle h;
	UNUSED(author);

	if (!name) {
		errno = EINVAL;
		return NULL;
	}
	
	if(!xdgInitHandle(&h))
		return NULL;
	
	ret = malloc(sizeof(*ret));
	if (!ret)
		return NULL;
	
	if (!(ret->data_dirs =
		appdir_dirs(name, xdgSearchableDataDirectories, &h))
		|| !(ret->cfg_dirs =
			appdir_dirs(name, xdgSearchableConfigDirectories, &h))
		|| !(ret->cache = appdir_home(name, xdgCacheHome, &h))
		|| !(ret->log = appdir_append(ret->cache, "/log")))
		return NULL;

	xdgWipeHandle(&h);
	return ret;
}
