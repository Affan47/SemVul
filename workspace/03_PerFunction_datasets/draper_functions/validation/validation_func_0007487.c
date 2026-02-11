stats_set_sizes(const char *dir, size_t num_files, size_t total_size)
{
	int fd;
	unsigned counters[STATS_END];
	char *stats_file;

	create_dir(dir);
	x_asprintf(&stats_file, "%s/stats", dir);

	memset(counters, 0, sizeof(counters));

	fd = safe_open(stats_file);
	if (fd != -1) {
		lock_fd(fd);
		stats_read_fd(fd, counters);
		counters[STATS_NUMFILES] = num_files;
		counters[STATS_TOTALSIZE] = total_size;
		write_stats(fd, counters);
		close(fd);
	}

	free(stats_file);
}
