getfreq(cp)
char *cp;
{
	long freq;

	if (!cp || !*cp) freq = 0L;
	else {
		*(cp++) = '\0';
		if ((freq = strtol(cp, NULL, 10)) < 0L) freq = 0L;
		else if (freq > MAXUTYPE(u_short)) freq = MAXUTYPE(u_short);
	}

	return((u_int)freq);
}
