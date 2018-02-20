#ifndef APPDIR_H
#define APPDIR_H

#ifdef __cplusplus
extern "C" {
#endif

char *appdir_data(const char *name, const char *author);
char **appdir_data_dirs(const char *name, const char *author);
char *appdir_cfg(const char *name, const char *author);
char **appdir_cfg_dirs(const char *name, const char *author);
char *appdir_cache(const char *name, const char *author);
char *appdir_log(const char *name, const char *author);

struct appdir {
	char **data_dirs;
	char **cfg_dirs;
	char *cache;
	char *log;
};

struct appdir *appdir(const char *name, const char *author);

#ifdef __cplusplus
}
#endif

#endif /* APPDIR_H */
