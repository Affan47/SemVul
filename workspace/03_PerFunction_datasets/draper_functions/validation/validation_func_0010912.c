parse_line(char* line,
	   guint64* start, guint64* end, char flags[4], guint64* offset,
	   gushort* dev_major, gushort* dev_minor, guint64* inode,
	   char** filename)
{


	char *p, *next;

	p = line;

	*start = strtoull(p, &p, 16);

	if (G_UNLIKELY(*p != '-'))
		return FALSE;
	p++;

	*end = strtoull(p, &p, 16);

	p = next_token(p);

	memcpy(flags, p, 4);
	p += 4;

	*offset = strtoull(p, &p, 16);

	*dev_major = strtoul(p, &p, 16);

	if (G_UNLIKELY(*p != ':'))
		return FALSE;
	p++;

	*dev_minor = strtoul(p, &p, 16);

	*inode = strtoull(p, &p, 10);

	p = next_token(p);

	*filename = p;

	for ( ; *p; p++) {
		if (*p == '\n') {
			*p = '\0';
			break;
		}
	}

	return TRUE;
}
