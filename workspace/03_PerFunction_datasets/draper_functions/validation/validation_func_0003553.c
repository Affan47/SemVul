mmap_file(char const *fname)
{
	fd_map = open(fname, O_RDONLY);
	if (fd_map < 0 || fstat(fd_map, &sb) < 0) {
		perror(fname);
		fail_file();
	}
	if (!S_ISREG(sb.st_mode)) {
		fprintf(stderr, "not a regular file: %s\n", fname);
		fail_file();
	}
	file_map = mmap(0, sb.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE,
			fd_map, 0);
	mmap_failed = 0;
	if (file_map == MAP_FAILED) {
		mmap_failed = 1;
		file_map = umalloc(sb.st_size);
		uread(fd_map, file_map, sb.st_size);
	}
	close(fd_map);

	file_end = file_map + sb.st_size;

	return file_map;
}
