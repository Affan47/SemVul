str_shifts(const char *str, unsigned *rmods, const char **rrest)
{
    *rmods = 0;
    *rrest = str;
    do {
	str = *rrest;
	for (int i = 0; i < ARRLEN(shifts); i++) {
	    if (strncmp(str, shifts[i].name, strlen(shifts[i].name)) == 0) {
		*rmods |= shifts[i].mask;
		*rrest += strlen(shifts[i].name);
	    }
	}
    } while (str != *rrest);

}
