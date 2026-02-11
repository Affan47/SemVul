isescaped(const char *sp, const char *p, int esc)
{
	const char     *cp;
	size_t		ne;

#if 0
	_DIAGASSERT(sp != NULL);
	_DIAGASSERT(p != NULL);
#endif


	if (esc == '\0')
		return 1;


	for (ne = 0, cp = p; --cp >= sp && *cp == esc; ne++)
		continue;


	return (ne & 1) != 0;
}
