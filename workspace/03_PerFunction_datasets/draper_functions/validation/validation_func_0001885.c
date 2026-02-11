git_mkstemps_mode(char *pattern, int suffix_len, int mode)
{
	static const char letters[] =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
	static const int num_letters = 62;
	uint64_t value;
	struct timeval tv;
	char *template;
	size_t len;
	int fd, count;

	len = strlen(pattern);

	if (len < 6 + suffix_len) {
		errno = EINVAL;
		return -1;
	}

	if (strncmp(&pattern[len - 6 - suffix_len], "XXXXXX", 6)) {
		errno = EINVAL;
		return -1;
	}


	gettimeofday(&tv, NULL);
	value = ((size_t)(tv.tv_usec << 16)) ^ tv.tv_sec ^ getpid();
	template = &pattern[len - 6 - suffix_len];
	for (count = 0; count < TMP_MAX; ++count) {
		uint64_t v = value;

		template[0] = letters[v % num_letters]; v /= num_letters;
		template[1] = letters[v % num_letters]; v /= num_letters;
		template[2] = letters[v % num_letters]; v /= num_letters;
		template[3] = letters[v % num_letters]; v /= num_letters;
		template[4] = letters[v % num_letters]; v /= num_letters;
		template[5] = letters[v % num_letters]; v /= num_letters;

		fd = open(pattern, O_CREAT | O_EXCL | O_RDWR, mode);
		if (fd > 0)
			return fd;


		if (errno != EEXIST)
			break;


		value += 7777;
	}

	pattern[0] = '\0';
	return -1;
}
