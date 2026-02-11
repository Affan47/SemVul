inode_create_symlink(struct inode *base, char *name,
	struct process *process, char *source_path)
{
	struct inode *inode;

	if (strlen(source_path) > GFARM_PATH_MAX) {
		gflog_debug(GFARM_MSG_1002432,
		    "create symlink \"%s\"  \"%s\": too long source path",
		    source_path, name);
		return (GFARM_ERR_FILE_NAME_TOO_LONG);
	}

	return (inode_lookup_relative(base, name, GFS_DT_LNK,
	    INODE_CREATE_EXCLUSIVE, process_get_user(process),
	    0777, source_path, &inode, NULL));
}
