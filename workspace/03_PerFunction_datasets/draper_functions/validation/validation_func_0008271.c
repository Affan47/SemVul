dir_alloc(void)
{
	Dir dir;

	GFARM_MALLOC(dir);
	if (dir == NULL) {
		gflog_debug(GFARM_MSG_1001708,
			"allocation of 'Dir' failed");
		return (NULL);
	}
	RB_INIT(dir);
	return (dir);
}
