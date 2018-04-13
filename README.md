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

## Dependencies

* `cmake`
* `xdg-basedir` on Linux

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Installing

If you are on a POSIX system, you can install with `make install`. You can
create a `.deb` or `.rpm` by configuring with `cmake -DCPACK_GENERATOR=RPM ..`,
or with `DEB` as appropriate, and run `make package`. If you would like to
create a tarball or zip, reconfigure with
`cmake -DCREATE_ARCHIVE=TRUE -DCPACK_GENERATOR=ZIP ..`, then run
`make package`. For a full list of valid generators, consult the
[CMake wiki](https://cmake.org/Wiki/CMake:CPackPackageGenerators#Bundle_.28OSX_only.29).

## Adding appdir to a CMake project

If you have installed appdir system-wide, you should be able to add appdir to
your project by adding `find_package(appdir)` to your `CMakeLists.txt`. If you
have downloaded an archive of appdir, add the `cmake` directory to the
`CMAKE_MODULE_PATH` before running `find_package(appdir)`:
`list(APPEND CMAKE_MODULE_PATH "PATH_TO_APPDIR_CMAKE_DIR)")`.
