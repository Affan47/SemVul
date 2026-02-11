typekludge(int ccall, register expptr q, Atype *at, int j)
#endif

{
	register int i, k;
	extern int iocalladdr;
	register Namep np;


	k = q->headblock.vtype;
	if (ccall) {
		if (k == TYREAL)
			k = TYDREAL;
		return k + 100;
		}
	if (k == TYADDR)
		return iocalladdr;
	i = q->tag;
	if ((i == TEXPR && q->exprblock.opcode != OPCOMMA_ARG)
	||  (i == TADDR && q->addrblock.charleng)
	||   i == TCONST)
		k = TYFTNLEN + 100;
	else if (i == TADDR)
	    switch(q->addrblock.vclass) {
		case CLPROC:
			if (q->addrblock.uname_tag != UNAM_NAME)
				k += 200;
			else if ((np = q->addrblock.user.name)->vprocclass
					!= PTHISPROC) {
				if (k && !np->vimpltype)
					k += 200;
				else {
					if (j > 200 && infertypes && j < 300) {
						k = j;
						inferdcl(np, j-200);
						}
					else k = (np->vstg == STGEXT
						? extsymtab[np->vardesc.varno].extype
						: 0) + 200;
					at->cp = mkchain((char *)np, at->cp);
					}
				}
			else if (k == TYSUBR)
				k += 200;
			break;

		case CLUNKNOWN:
			if (q->addrblock.vstg == STGARG
			 && q->addrblock.uname_tag == UNAM_NAME) {
				k += 400;
				at->cp = mkchain((char *)q->addrblock.user.name,
						at->cp);
				}
		}
	else if (i == TNAME && q->nameblock.vstg == STGARG) {
		np = &q->nameblock;
		switch(np->vclass) {
		    case CLPROC:
			if (!np->vimpltype)
				k += 200;
			else if (j <= 200 || !infertypes || j >= 300)
				k += 300;
			else {
				k = j;
				inferdcl(np, j-200);
				}
			goto add2chain;

		    case CLUNKNOWN:

			if (np->vimpltype && j && infertypes
			&& j < 300) {
				inferdcl(np, j % 100);
				k = j;
				}
			else
				k += 400;


 add2chain:
			at->cp = mkchain((char *)np, at->cp);
		    }
		}
	return k;
	}
