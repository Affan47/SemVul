cli_ftw(char *path, int flags, int maxdepth, cli_ftw_cb callback, struct cli_ftw_cbdata *data, cli_ftw_pathchk pathchk)
{
    STATBUF statbuf;
    enum filetype ft = ft_unknown;
    struct dirent_data entry;
    int stated = 0;
    int ret;

    if (((flags & CLI_FTW_TRIM_SLASHES) || pathchk) && path[0] && path[1]) {
	char *pathend;


#ifndef _WIN32
	while (path[0] == *PATHSEP && path[1] == *PATHSEP) path++;
#endif
	pathend = path + strlen(path);
	while (pathend > path && pathend[-1] == *PATHSEP) --pathend;
	*pathend = '\0';
    }
    if(pathchk && pathchk(path, data) == 1)
	return CL_SUCCESS;
    ret = handle_filetype(path, flags, &statbuf, &stated, &ft, callback, data);
    if (ret != CL_SUCCESS)
	return ret;
    if (ft_skipped(ft))
	return CL_SUCCESS;
    entry.statbuf = stated ? &statbuf : NULL;
    entry.is_dir = ft == ft_directory;
    entry.filename = entry.is_dir ? NULL : strdup(path);
    entry.dirname = entry.is_dir ? path : NULL;
    if (entry.is_dir) {
	ret = callback(entry.statbuf, NULL, path, visit_directory_toplev, data);
	if (ret != CL_SUCCESS)
	    return ret;
    }
    return handle_entry(&entry, flags, maxdepth, callback, data, pathchk);
}
