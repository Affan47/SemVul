addhinsidict(VOID_A)
{
	ALLOC_T ptr, klen;
	int i;

	for (i = 0; i < CONLISTSIZ; i++) {
		ptr = maxstr;
		if (setkbuf(conlist[i].klen, conlist[i].kbuf) < 0) return(-1);
		klen = maxstr - ptr;
		if (setkbuf(conlist[i].klen, conlist[i].kbuf) < 0) return(-1);
		if (setword(0) < 0) return(-1);
		if (setkbuf(1, &(conlist[i].id)) < 0) return(-1);

		if (adddictlist(ptr, klen, maxstr - ptr - klen)) return(-1);
	}

	return(0);
}
