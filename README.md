# appdir

appdir is a library for finding platform-specific dirs. Unfortunately, there
is no platform-agnostic way to open a file given a directory and a filename.
There are several file libraries for C which provide this and more already
(e.g. [APR](https://apr.apache.org/docs/apr/trunk/group__apr__file__io.html),
[CZMQ](http://czmq.zeromq.org/czmq4-0:zfile),
and [glib](https://developer.gnome.org/glib/stable/glib-File-Utilities.html)).
However, none of them have facilities for finding data, configuration,
cache, and logging directories, which is what this library aims to provide.

```c
char *dir;
size_t i;
char *cfg_dirs = appdir_cfg_dirs("name", "author");
for (i = 0; (dir = cfg_dirs[i]); i++) {
	/* Search for a configuration file */
}
appdir_list_put(cfg_dirs);
```
