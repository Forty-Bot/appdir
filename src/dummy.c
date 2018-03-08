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
#include <stdio.h>

#ifndef ENOSYS
#define ENOSYS 38
#endif

#define UNIMPLEMENTED UNUSED(name); UNUSED(author); errno = ENOSYS; return NULL

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
