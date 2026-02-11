display(void)
{
	register FS *fs;
	register FU *fu;
	register PR *pr;
	register int cnt;
	register unsigned char *bp;
	off_t saveaddress;
	unsigned char savech = 0, *savebp;

	while ((bp = get()) != NULL)
	    for (fs = fshead, savebp = bp, saveaddress = address; fs;
		fs = fs->nextfs, bp = savebp, address = saveaddress)
		    for (fu = fs->nextfu; fu; fu = fu->nextfu) {
			if (fu->flags&F_IGNORE)
				break;
			for (cnt = fu->reps; cnt; --cnt)
			    for (pr = fu->nextpr; pr; address += pr->bcnt,
				bp += pr->bcnt, pr = pr->nextpr) {
				    if (eaddress && address >= eaddress &&
					!(pr->flags&(F_TEXT|F_BPAD)))
					    bpad(pr);
				    if (cnt == 1 && pr->nospace) {
					savech = *pr->nospace;
					*pr->nospace = '\0';
				    }
				    print(pr, bp);
				    if (cnt == 1 && pr->nospace)
					*pr->nospace = savech;
			    }
		    }
	if (endfu) {


		if (!eaddress) {
			if (!address)
				return;
			eaddress = address;
		}
		for (pr = endfu->nextpr; pr; pr = pr->nextpr)
			switch(pr->flags) {
			case F_ADDRESS:
				(void)printf(pr->fmt, (int64_t)eaddress);
				break;
			case F_TEXT:
				(void)printf("%s", pr->fmt);
				break;
			}
	}
}
