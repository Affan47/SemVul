gfs_dirplus_alloc(struct gfm_connection *gfm_server, gfarm_int32_t fd,
	GFS_DirPlus *dirp)
{
	GFS_DirPlus dir;

	GFARM_MALLOC(dir);
	if (dir == NULL) {
		gflog_debug(GFARM_MSG_1001277,
			"allocation of dir failed: %s",
			gfarm_error_string(GFARM_ERR_NO_MEMORY));
		return (GFARM_ERR_NO_MEMORY);
	}

	dir->gfm_server = gfm_server;
	dir->fd = fd;
	dir->n = dir->index = 0;

	*dirp = dir;
	return (GFARM_ERR_NO_ERROR);
}
