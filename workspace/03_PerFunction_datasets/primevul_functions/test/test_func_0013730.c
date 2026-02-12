strdelim_internal(char **s, int split_equals)
{
	char *old;
	int wspace = 0;

	if (*s == NULL)
		return NULL;

	old = *s;

	*s = strpbrk(*s,
	    split_equals ? WHITESPACE QUOTE "=" : WHITESPACE QUOTE);
	if (*s == NULL)
		return (old);

	if (*s[0] == '\"') {
		memmove(*s, *s + 1, strlen(*s));

		if ((*s = strpbrk(*s, QUOTE)) == NULL) {
			return (NULL);
		} else {
			*s[0] = '\0';
			*s += strspn(*s + 1, WHITESPACE) + 1;
			return (old);
		}
	}


	if (split_equals && *s[0] == '=')
		wspace = 1;
	*s[0] = '\0';


	*s += strspn(*s + 1, WHITESPACE) + 1;
	if (split_equals && *s[0] == '=' && !wspace)
		*s += strspn(*s + 1, WHITESPACE) + 1;

	return (old);
}
