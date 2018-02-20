#include "appdir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Stolen from <http://www.jera.com/techinfo/jtns/jtn002.html> */
#define stringify2(x) #x
#define stringify(x) stringify2(x)
#define __LINE_STR__ stringify(__LINE__)
#define assert(message, test) do { if (!(test)) \
	return (__FILE__ ":" __LINE_STR__ ": " message); } while (0)
#define assert_nonnull(var) assert(#var " is NULL", (var))
#define assert_eq(x, y) assert(#x " does not equal " #y, (x) == (y))
#define assert_streq(x, y) assert(#x " does not equal " #y, !strcmp((x), (y)))

/* Test basic equalities and equivalencies */
char *test_equiv() {
	char *dir;
	char **dirs;
	struct appdir *ad;
	
	ad = appdir_get("name", "author");
	assert_nonnull(ad);

#define assert_strlisteq(l1, l2) \
	do { \
		size_t i; \
		assert_nonnull(l1); \
		assert_nonnull(l2); \
		for (i = 0; l1[i] && l2[i]; i++) { \
			assert_nonnull(l1[i]); \
			assert_nonnull(l2[i]); \
			assert_streq(l1[i], l2[i]); \
		} \
		assert_eq(l1[i], l2[i]); \
		assert("One of " #l1 " or " #l2 " is empty", i > 0); \
	} while (0)

	dirs = appdir_data_dirs("name", "author");
	assert_strlisteq(ad->data_dirs, dirs);
	appdir_list_put(dirs);

	dirs = appdir_cfg_dirs("name", "author");
	assert_strlisteq(ad->cfg_dirs, dirs);
	appdir_list_put(dirs);
	
	assert_nonnull(ad->cache);
	dir = appdir_cache("name", "author");
	assert_nonnull(dir);
	assert_streq(ad->cache, dir);
	free(dir);

	assert_nonnull(ad->log);
	dir = appdir_log("name", "author");
	assert_nonnull(dir);
	assert_streq(ad->log, dir);
	free(dir);

	appdir_put(ad);
	return 0;
}

int main() {
	char *res = test_equiv();
	if (res)
		fprintf(stderr, "%s\n", res);

	return !!res;
}
