chirp_fs_hdfs_utime(const char *path, time_t actime, time_t modtime)
{
	path = FIXPATH(path);
	debug(D_HDFS, "utime %s %ld %ld", path, (long) actime, (long) modtime);
	return hdfs_services->utime(fs, path, modtime, actime);
}
