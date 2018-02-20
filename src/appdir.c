#include "appdir.h"

#include <stdlib.h>

void appdir_list_put(char **dirs) {
	size_t i;

	if (!dirs)
		return;

	for (i = 0; dirs[i]; i++)
		free(dirs[i]);

	free(dirs);
}

void appdir_put(struct appdir *ad) {
	if (!ad)
		return;

	appdir_list_put(ad->data_dirs);
	appdir_list_put(ad->cfg_dirs);
	if (ad->cache)
		free(ad->cache);
	if (ad->log)
		free(ad->log);
	free(ad);
}
