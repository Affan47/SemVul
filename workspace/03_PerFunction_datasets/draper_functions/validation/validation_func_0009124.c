strcmp_nospace(char *s1, char *s2)
{
	while (*s1 && *s2) {
		while (isspace(*s1))
			s1++;
		while (isspace(*s2))
			s2++;
		if (*s1 > *s2)
			return 1;
		if (*s1 < *s2)
			return -1;
		s1++;
		s2++;
	}
	return 0;
}
