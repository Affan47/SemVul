fileinit(Void)
{
	register char *s;
	register int i, j;

	lastiolabno = 100000;
	lastlabno = 0;
	lastvarno = 0;
	nliterals = 0;
	nerr = 0;

	infile = stdin;

	maxtoklen = 502;
	token = (char *)ckalloc(maxtoklen+2);
	memset(dflttype, tyreal, 26);
	memset(dflttype + ('i' - 'a'), tyint, 6);
	memset(hextoi_tab, 16, sizeof(hextoi_tab));
	for(i = 0, s = "0123456789abcdef"; *s; i++, s++)
		hextoi(*s) = i;
	for(i = 10, s = "ABCDEF"; *s; i++, s++)
		hextoi(*s) = i;
	for(j = 0, s = "abcdefghijklmnopqrstuvwxyz"; i = *s++; j++)
		Letters[i] = Letters[i+'A'-'a'] = j;
#ifdef TYQUAD


	ff = 0xffff;
	ff = (ff << 16) | ff;
#endif
	ctls = ALLOCN(maxctl+1, Ctlframe);
	extsymtab = ALLOCN(maxext, Extsym);
	eqvclass = ALLOCN(maxequiv, Equivblock);
	hashtab = ALLOCN(maxhash, Hashentry);
	labeltab = ALLOCN(maxstno, Labelblock);
	litpool = ALLOCN(maxliterals, Literal);
	labarray = (struct Labelblock **)ckalloc(maxlablist*
					sizeof(struct Labelblock *));
	fmt_init();
	mem_init();
	np_init();

	ctlstack = ctls++;
	lastctl = ctls + maxctl;
	nextext = extsymtab;
	lastext = extsymtab + maxext;
	lasthash = hashtab + maxhash;
	labtabend = labeltab + maxstno;
	highlabtab = labeltab;
	main_alias[0] = '\0';
	if (forcedouble)
		dfltproc[TYREAL] = dfltproc[TYDREAL];


	out_init ();
}
