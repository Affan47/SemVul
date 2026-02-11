gmem(int n, int round)
#endif
{
	static char *last, *next;
	char *rv;
	if (round)
#ifdef CRAY
		if ((long)next & 0xe000000000000000)
			next = (char *)(((long)next & 0x1fffffffffffffff) + 1);
#else
#ifdef MSDOS
		if ((int)next & 1)
			next++;
#else
		next = (char *)(((long)next + sizeof(char *)-1)
				& ~((long)sizeof(char *)-1));
#endif
#endif
	rv = next;
	if ((next += n) > last) {
		rv = Alloc(n + GMEMBSIZE);

		next = rv + n;
		last = next + GMEMBSIZE;
		}
	return rv;
	}
