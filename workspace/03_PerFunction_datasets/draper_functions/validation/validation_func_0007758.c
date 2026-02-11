inetntoa(const char *in)
{
	static char buf[16];
	char *bufptr = buf;
	const unsigned char *a = (const unsigned char *)in;
	const char *n;

	n = IpQuadTab[*a++];
	while(*n)
		*bufptr++ = *n++;
	*bufptr++ = '.';
	n = IpQuadTab[*a++];
	while(*n)
		*bufptr++ = *n++;
	*bufptr++ = '.';
	n = IpQuadTab[*a++];
	while(*n)
		*bufptr++ = *n++;
	*bufptr++ = '.';
	n = IpQuadTab[*a];
	while(*n)
		*bufptr++ = *n++;
	*bufptr = '\0';
	return buf;
}
