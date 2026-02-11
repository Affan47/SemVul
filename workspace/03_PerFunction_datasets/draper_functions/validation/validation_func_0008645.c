cfs_lookup(const char *url)
{
	if(!strchr(url, ':') || !strncmp(url, "local:", 6) || !strncmp(url, "file:", 5)) {
		return &chirp_fs_local;
	} else if(!strncmp(url, "hdfs:", 5)) {
		return &chirp_fs_hdfs;
	} else if(!strncmp(url, "chirp:", 6)) {
		return &chirp_fs_chirp;
	} else {
		return 0;
	}
}
