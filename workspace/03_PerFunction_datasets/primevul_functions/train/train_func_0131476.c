static int match_wildcard_base(const struct pathspec_item *item,
			       const char *base, int baselen,
			       int *matched)
{
	const char *match = item->match;

	int matchlen = item->nowildcard_len;

	if (baselen) {
		int dirlen;


		if (baselen >= matchlen) {
			*matched = matchlen;
			return !basecmp(item, base, match, matchlen);
		}

		dirlen = matchlen;
		while (dirlen && match[dirlen - 1] != '/')
			dirlen--;


		if (basecmp(item, base, match, baselen))
			return 0;
		*matched = baselen;
	} else
		*matched = 0;


	return entry_interesting;
}
