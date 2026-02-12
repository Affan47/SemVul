static inline void phar_unixify_path_separators(char *path, int path_len)
{
	char *s;


	for (s = path; s - path < path_len; ++s) {
		if (*s == '\\') {
			*s = '/';
		}
	}
}
