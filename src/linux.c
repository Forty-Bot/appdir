#include "appdir.h"
#include "internal.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <basedir.h>

#define DIR_SEP '/'

static char *__appdir_home(const char *name,
			 const char *xdg_home(xdgHandle *), xdgHandle *h) {
	const char *home;
	char *ret;
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
	memcpy(ret, home, home_len);
	ret[home_len] = DIR_SEP;
	memcpy(ret + home_len + 1, name, name_len);
	ret[ret_len] = '\0';
	return ret;
}

char *appdir_data(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_home(name, xdgDataHome, NULL);
}

static char **__appdir_dirs(const char *name,
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
		size_t dir_len = strlen(dirs[i]);
		size_t ret_len = dir_len + 1 + name_len;

		ret[i] = malloc(ret_len + 1);
		if (!ret[i])
			return NULL;
		
		memcpy(ret[i], dirs[i], dir_len);
		ret[i][dir_len] = DIR_SEP;
		memcpy(ret[i] + dir_len + 1, name, name_len);
		ret[i][ret_len] = '\0';
	}
	ret[dirs_len] = NULL;

	return ret;
}

char **appdir_data_dirs(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_dirs(name, xdgSearchableDataDirectories, NULL);
}

char *appdir_cfg(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_home(name, xdgConfigHome, NULL);
}

char **appdir_cfg_dirs(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_dirs(name, xdgSearchableConfigDirectories, NULL);
}

char *appdir_cache(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_home(name, xdgCacheHome, NULL);
}

static const char log[] = "/log";
static char *__appdir_log(const char *cache) {
	size_t cache_len;
	char *ret;

	if (!cache)
		return NULL;
	cache_len = strlen(cache);

	/* sizeof(log) includes the null terminator */
	ret = malloc(cache_len + sizeof(log));
	if (!ret)
		return NULL;

	memcpy(ret, cache, cache_len);
	memcpy(ret + cache_len, log, sizeof(log));
	return ret;
}

char *appdir_log(const char *name, const char *author) {
	UNUSED(author);
	return __appdir_log(__appdir_home(name, xdgCacheHome, NULL));
}

struct appdir *appdir(const char *name, const char *author) {
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
		__appdir_dirs(name, xdgSearchableDataDirectories, &h))
		|| !(ret->cfg_dirs =
			__appdir_dirs(name, xdgSearchableConfigDirectories, &h))
		|| !(ret->cache = __appdir_home(name, xdgCacheHome, &h))
		|| !(ret->log = __appdir_log(ret->cache)))
		return NULL;

	xdgWipeHandle(&h);
	return ret;
}
