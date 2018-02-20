#include "appdir.h"

#include <errno.h>
#include <stdio.h>

#ifndef ENOSYS
#define ENOSYS 38
#endif

#define UNIMPLEMENTED errno = ENOSYS; return NULL

char *appdir_data(const char *name, const char *author) {
	UNIMPLEMENTED;
}

char **appdir_data_dirs(const char *name, const char *author) {
	UNIMPLEMENTED;
}

char *appdir_cfg(const char *name, const char *author) {
	UNIMPLEMENTED;
}

char **appdir_cfg_dirs(const char *name, const char *author) {
	UNIMPLEMENTED;
}

char *appdir_cache(const char *name, const char *author) {
	UNIMPLEMENTED;
}

char *appdir_log(const char *name, const char *author) {
	UNIMPLEMENTED;
}

struct appdir *appdir_get(const char *name, const char *author) {
	UNIMPLEMENTED;
}
