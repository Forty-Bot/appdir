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
#include "internal.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define DIR_SEP '\\'

static char *appdir_getenv(const char *name, const char *author,
			   const char *envname) {
	char *env;
	char *ret;
	char *p;
	size_t env_len;
	size_t author_len;
	size_t name_len;
	size_t ret_len;

	if (!name) {
		errno = EINVAL;
		return NULL;
	}
	name_len = strlen(name);

	if (!author)
		author = name;
	author_len = strlen(author);

	env = getenv(envname);
	if (!env || !env[0]) {
		errno = EINVAL;
		return NULL;
	}
	env_len = strlen(env);

	ret_len = env_len + 1 + author_len + 1 + name_len;
	ret = malloc(ret_len + 1);
	if (!ret)
		return NULL;
	p = ret;

	memcpy(p, env, env_len);
	p += env_len;

	*p++ = DIR_SEP;

	memcpy(p, author, author_len);
	p += author_len;

	*p++ = DIR_SEP;
	
	memcpy(p, name, name_len);
	p += name_len;
	
	*p = '\0';

	return ret;
}

char *appdir_data(const char *name, const char *author) {
	return appdir_getenv(name, author, "APPDATA");
}

static char **appdir_getenv_list(const char *name, const char *author,
				 const char *const *envs, size_t n) {
	char **dirs;
	size_t i;

	dirs = malloc(sizeof(*dirs) * (n + 1));
	if (!dirs)
		return NULL;

	for (i = 0; i < n; i++) {
		dirs[i] = appdir_getenv(name, author, envs[i]);
		if (!dirs[i]) {
			size_t j;
			for (j = 0; j < i; j++)
				free(dirs[j]);
			free(dirs);
			return NULL;
		}
	}
	dirs[i] = NULL;

	return dirs;
}

static const char *const data_dirs_env[] = {"APPDATA", "ProgramFiles"};
char **appdir_data_dirs(const char *name, const char *author) {
	return appdir_getenv_list(name, author, data_dirs_env, 2);
}

char *appdir_cfg(const char *name, const char *author) {
	return appdir_data(name, author);
}

static const char *const cfg_dirs_env[] = {"APPDATA", "ProgramData"};
char **appdir_cfg_dirs(const char *name, const char *author) {
	return appdir_getenv_list(name, author, cfg_dirs_env, 2);
}

char *appdir_cache(const char *name, const char *author) {
	char *ret;
	char *data = appdir_data(name, author);
	
	if (!data)
		return NULL;
	ret = appdir_append(data, "\\Cache");
	free(data);

	return ret;
}

char *appdir_log(const char *name, const char *author) {
	char *ret;
	char *data = appdir_data(name, author);
	
	if (!data)
		return NULL;
	ret = appdir_append(data, "\\Logs");
	free(data);

	return ret;
}

struct appdir *appdir_get(const char *name, const char *author) {
	struct appdir *ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return NULL;

	if(!(ret->data_dirs = appdir_data_dirs(name, author))
		|| !(ret->cfg_dirs = appdir_cfg_dirs(name, author))
		|| !(ret->cache = appdir_append(ret->data_dirs[0], "\\Cache"))
		|| !(ret->log = appdir_append(ret->data_dirs[0], "\\Logs")))
		return NULL;

	return ret;
}
