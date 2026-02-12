XFreeFontNames(char **list)
{
	if (list) {
		if (!*(list[0]-1)) {
			register char **names;
			for (names = list+1; *names; names++)
				Xfree (*names);
		}
		Xfree (list[0]-1);
		Xfree (list);
	}
	return 1;
}
