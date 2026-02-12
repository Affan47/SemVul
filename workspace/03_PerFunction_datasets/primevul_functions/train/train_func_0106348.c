static int tree_entry_interesting(struct tree_desc *desc, const char *base, int baselen, struct diff_options *opt)
{
	const char *path;
	const unsigned char *sha1;
	unsigned mode;
	int i;
	int pathlen;
	int never_interesting = -1;

	if (!opt->nr_paths)
		return 1;

	sha1 = tree_entry_extract(desc, &path, &mode);

	pathlen = tree_entry_len(path, sha1);

	for (i = 0; i < opt->nr_paths; i++) {
		const char *match = opt->paths[i];
		int matchlen = opt->pathlens[i];
		int m = -1;

		if (baselen >= matchlen) {

			if (strncmp(base, match, matchlen))
				continue;


			return 2;
		}


		if (strncmp(base, match, baselen))
			continue;

		match += baselen;
		matchlen -= baselen;

		if (never_interesting) {


			m = strncmp(match, path,
				    (matchlen < pathlen) ? matchlen : pathlen);
			if (m < 0)
				continue;


			never_interesting = 0;
		}

		if (pathlen > matchlen)
			continue;

		if (matchlen > pathlen) {
			if (match[pathlen] != '/')
				continue;
			if (!S_ISDIR(mode))
				continue;
		}

		if (m == -1)


			m = strncmp(match, path, pathlen);


		if (!m)
			return 1;
	}
	return never_interesting;
}
