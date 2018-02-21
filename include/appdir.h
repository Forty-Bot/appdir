#ifndef APPDIR_H
#define APPDIR_H

/** \file appdir.h
 *  \brief The public api of c-appdir.
 *
 *  Some implementations rely on `getenv` to determine directories. Calling
 *  `setenv` while in any function except appdir_list_put() or appdir_put() in
 *  c-appdir may cause a data-race. **None of the functions in c-appdir are
 *  thread-safe** for this reason. Call c-appdir functions before spawning
 *  threads which call `setenv`.
 *
 *  All returned values are allocated with `malloc` and can be `free`'d either
 *  piecemeal, or with appdir_list_put() or appdir_put().
 */

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Get the per-user data directory
 *
 *  This is the location to store any user-specific data. It should be writable
 *  by default on all systems. Typical values for various operating systems
 *  include
 *  - **Linux** `~/.local/share/<name>` (corresponding to `$XDG_DATA_HOME`)
 *  - **Windows** `C:\Users\<user>\AppData\Roaming\<author>\<name>`
 *  (corresponding to `%%APPDATA%`)
 *  - **Darwin** `~/Library/Application Support/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d string containing the data directory. On error, `NULL`
 *  is returned and `errno` is set.
 */
char *appdir_data(const char *name, const char *author);

/** \brief Get a list of searchable data directories
 *
 *  Search within each of the returned directories in order to find data files.
 *  The first directory in the list is the same as the one returned by
 *  appdir_data(). Some (but not all) directories may be writable. Typical
 *  entries for various operating systems in addition to the first entry include
 *  - **Linux** `/usr/local/share/<name>` and `/usr/share/<name>` (corresponding
 *  to `$XDG_DATA_DIRS`)
 *  - **Windows** `C:\Program Files\<author>\<name>` (corresponding to
 *  `%%ProgramFiles%`)
 *  - **Darwin** `/Library/Application Support/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d `NULL`-terminated list of strings allocated with
 *  `malloc`. They can be `free`'d individually, or by using appdir_list_put().
 *  On error, `NULL` is returned and `errno` is set.
 */
char **appdir_data_dirs(const char *name, const char *author);

/** \brief Get the per-user configuration directory
 *
 *  This is the location to store any user-specific configuration files. It
 *  should be writable by default on all systems. Typical default values for
 *  various operating systems include
 *  - **Linux** `~/.config/<name>` (corresponding to `$XDG_CONFIG_HOME`)
 *  - **Windows** appdir_data()
 *  - **Darwin** `~/Library/Preferences/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d string containing the configuration directory. On
 *  error, `NULL` is returned and `errno` is set.
 */
char *appdir_cfg(const char *name, const char *author);

/** \brief Get a list of searchable configuration directories
 *
 *  Search within each of the returned directories in order to find
 *  configuration files. The first directory in the list is the same as the one
 *  returned by appdir_cfg(). Some (but not all) directories may be writable.
 *  Typical entries for various operating systems in addition to the first entry
 *  include
 *  - **Linux** `/etc/xdg` (corresponding to `$XDG_CONFIG_DIRS`)
 *  - **Windows** `C:\ProgramData\<author>\<name>` (corresponding to
 *  `%%ProgramData%`)
 *  - **Darwin** appdir_data_dirs()
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d `NULL`-terminated list of strings allocated with
 *  `malloc`. They can be `free`'d individually, or by using appdir_list_put().
 *  On error, `NULL` is returned and `errno` is set.
 */
char **appdir_cfg_dirs(const char *name, const char *author);

/** \brief Get the per-user cache directory
 *
 *  This is the location to store any user-specific cache files. It should be
 *  writable by default on all systems. There is no `appdir_cache_dirs` because
 *  there is no platform-agnostic equivalent of a global cache. Typical default
 *  values for various operating systems include
 *  - **Linux** `~/.cache/<name>` (corresponding to `$XDG_CACHE_HOME`)
 *  - **Windows** appdir_data()`/Cache`
 *  - **Darwin** `~/Library/Caches/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d string containing the cache directory. On error, `NULL`
 *  is returned and `errno` is set.
 */
char *appdir_cache(const char *name, const char *author);

/** \brief Get the per-user logging directory
 *
 *  This is the location to store any user-specific log files. It should be
 *  writable by default on all systems. There is no `appdir_log_dirs` because
 *  there is no platform-agnostic readable log directory. Typical default
 *  values for various operating systems include
 *  - **Linux** appdir_data()/`log`
 *  - **Windows** appdir_data()`/Logs`
 *  - **Darwin** `~/Library/Logs/<name>`
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d string containing the logging directory. On error,
 *  `NULL` is returned and `errno` is set.
 */
char *appdir_log(const char *name, const char *author);

/** \brief Put a list of strings
 *
 *  This function is a utility function to `free` all memory of a list of strings
 *  (or other `malloc`'d pointers), such as those returned by appdir_data_dirs()
 *  and appdir_cfg_dirs().
 *
 *  \param dirs The list of strings to `free`.
 */
void appdir_list_put(char **dirs);

/** \brief A convenience struct returned by appdir_get()
 *
 *  \sa appdir_get appdir_put
 */
struct appdir {
	/** \brief Holds the return value of appdir_data_dirs() */
	char **data_dirs;
	/** \brief Holds the return value of appdir_cfg_dirs() */
	char **cfg_dirs;
	/** \brief Holds the return value of appdir_cache() */
	char *cache;
	/** \brief Holds the return value of appdir_log() */
	char *log;
};

/** \brief Creates a struct containing the values of the rest of the api
 *
 *  Collects the values of appdir_data_dirs(), appdir_cfg_dirs(),
 *  appdir_cache(), and appdir_log(). This function may be faster than calling
 *  each function individually on some platforms.
 *
 *  \param name The name of your program
 *  \param author The author or organization which produced the program. This
 *  defaults to \a name.
 *  \return A `malloc`'d and appropriately initialized `struct` \ref appdir. On
 *  error, `NULL` is returned and `errno` is set.
 *  \sa appdir_put
 */
struct appdir *appdir_get(const char *name, const char *author);

/** \brief Recursively frees a `struct` \ref appdir created by appdir_get()
 *
 *  \param ad The struct to free
 *  \sa appdir_get
 */
void appdir_put(struct appdir *ad);

#ifdef __cplusplus
}
#endif

#endif /* APPDIR_H */
