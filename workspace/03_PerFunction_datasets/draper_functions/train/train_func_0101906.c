F77_aloc(integer Len, const char *whence)
#endif
{
	char *rv;
	unsigned int uLen = (unsigned int) Len;

	if (!(rv = (char*)malloc(uLen))) {
		fprintf(stderr, "malloc(%u) failure in %s\n",
			uLen, whence);
		exit_(&memfailure);
		}
	return rv;
	}
