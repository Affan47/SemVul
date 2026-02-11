define(table, abbrev, phrase)
register struct abbrev	*table[HASHSIZE];
char	*abbrev,
	*phrase;
{
	register struct abbrev	*ap;

	ap = lookup_abbrev(table, abbrev);
	if (ap == NULL) {
		register unsigned int	h = hash(abbrev);

		ap = (struct abbrev *) emalloc(sizeof *ap);
		ap->a_hash = h;
		ap->a_abbrev = copystr(abbrev);
		h %= HASHSIZE;
		ap->a_next = table[h];
		ap->a_cmdhook = NULL;
		table[h] = ap;
	} else
		free((UnivPtr) ap->a_phrase);
	ap->a_phrase = copystr(phrase);
}
