#ifndef APPDIR_H
#define APPDIR_H

/** \file appdir.h
 *  \brief Contains all public-facing functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Get the per-user data directory
 *  
 *  This is the location to store any user-specific data. It should be writable
 *  by default on all systems. Typical default values for various operating
 *  systems include
 *  - **Linux** `~/.local/share/<name>` (corresponding to `$XDG_DATA_HOME`)
 *  - **Windows** `C:\Users\<user>\AppData\Roaming\<author>\<name>` (corresponding
 *  to `%APPDATA%`)
 *  - **Darwin** `~/Library/Application Support/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to name.
 *  \return A `malloc`'d string containing the data directory.
 */
char *appdir_data(const char *name, const char *author);
char **appdir_data_dirs(const char *name, const char *author);
char *appdir_cfg(const char *name, const char *author);
char **appdir_cfg_dirs(const char *name, const char *author);
char *appdir_cache(const char *name, const char *author);
char *appdir_log(const char *name, const char *author);

void appdir_list_put(char **dirs);

struct appdir {
	char **data_dirs;
	char **cfg_dirs;
	char *cache;
	char *log;
};

struct appdir *appdir_get(const char *name, const char *author);
void appdir_put(struct appdir *ad);

#ifdef __cplusplus
}
#endif

#endif /* APPDIR_H */
