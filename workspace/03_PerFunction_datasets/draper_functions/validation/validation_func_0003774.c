evalposixsubst(s, ptrp)
CONST char *s;
int *ptrp;
{
#ifndef	BASHBUG
	syntaxtree *trp, *stree;
	redirectlist red;
#endif
	char *cp, *new;
	long n;
	int i, len;

	i = 1;
	if (s[i] == '(') i++;

	s += i;
	len = *ptrp - i * 2;
	s = new = Xstrndup(s, len);
	if (i <= 1) {
#ifndef	BASHBUG

		red.fd = red.type = red.new = 0;
		red.filename = vnullstr;
		i = len = 0;
		stree = newstree(NULL);
		trp = startvar(stree, &red, nullstr, &i, &len, 0);
		trp -> cont = CN_COMM;
		trp = analyze(s, trp, -1);
		if (trp && (trp -> cont & CN_SBST) != CN_CASE) trp = NULL;
		freestree(stree);
		Xfree(stree);
		if (trp) cp = NULL;
		else
#endif
		if (!(cp = evalbackquote(s))) *ptrp = -1;
	}
	else {
		n = 0L;
		cp = evalvararg(new,
			EA_STRIPESCAPE
			| EA_NOEVALQ | EA_NOEVALDQ | EA_BACKQ, 0);
		if (!cp) *ptrp = -1;
		else {
			for (i = 0; cp[i]; i++)
				if (!Xstrchr(IFS_SET, cp[i])) break;
			if (cp[i]) {
				i = evalexpression(cp, i, &n, 9);
				if (i < 0 || cp[i]) *ptrp = -1;
			}
			Xfree(cp);
		}

		cp = (*ptrp < 0) ? NULL : asprintf2("%ld", n);
	}
	Xfree(new);

	return(cp);
}
