latlon2ul (const char **latlonstrptr, int *which)
{
	const char *cp;
	u_int32_t retval;
	int deg = 0, min = 0, secs = 0, secsfrac = 0;

	cp = *latlonstrptr;

	while (isdigit(*cp))
		deg = deg * 10 + (*cp++ - '0');

	while (isspace(*cp))
		cp++;

	if (!(isdigit(*cp)))
		goto fndhemi;

	while (isdigit(*cp))
		min = min * 10 + (*cp++ - '0');

	while (isspace(*cp))
		cp++;

	if (!(isdigit(*cp)))
		goto fndhemi;

	while (isdigit(*cp))
		secs = secs * 10 + (*cp++ - '0');

	if (*cp == '.') {
		cp++;
		if (isdigit(*cp)) {
			secsfrac = (*cp++ - '0') * 100;
			if (isdigit(*cp)) {
				secsfrac += (*cp++ - '0') * 10;
				if (isdigit(*cp)) {
					secsfrac += (*cp++ - '0');
				}
			}
		}
	}

	while (!isspace(*cp))
		cp++;

	while (isspace(*cp))
		cp++;

 fndhemi:
	switch (*cp) {
	case 'N': case 'n':
	case 'E': case 'e':
		retval = ((unsigned)1<<31)
			+ (((((deg * 60) + min) * 60) + secs) * 1000)
			+ secsfrac;
		break;
	case 'S': case 's':
	case 'W': case 'w':
		retval = ((unsigned)1<<31)
			- (((((deg * 60) + min) * 60) + secs) * 1000)
			- secsfrac;
		break;
	default:
		retval = 0;
		break;
	}

	switch (*cp) {
	case 'N': case 'n':
	case 'S': case 's':
		*which = 1;
		break;
	case 'E': case 'e':
	case 'W': case 'w':
		*which = 2;
		break;
	default:
		*which = 0;
		break;
	}

	cp++;

	while (!isspace(*cp))
		cp++;

	while (isspace(*cp))
		cp++;

	*latlonstrptr = cp;

	return (retval);
}
