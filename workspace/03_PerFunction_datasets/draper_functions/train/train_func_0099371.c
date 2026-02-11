initroman(VOID_A)
{
	int i, n;

	if (romanlist) return;
	if (!(romanlist = (romantable *)malloc(sizeof(origromanlist)))) return;

	memcpy((char *)romanlist, (char *)origromanlist,
		sizeof(origromanlist));
	for (n = 0; n < ROMANLISTSIZ; n++) {
		for (i = 0; i < R_MAXKANA; i++) {
			if (!romanlist[n].code[i]) continue;
			if (romanlist[n].code[i] & ~0xff) continue;
			romanlist[n].code[i] |= 0x2400;
		}
	}

	maxromanlist = ROMANLISTSIZ;
	for (i = 0; i < CATROMANLISTSIZ; i++) {
		n = catroman(catromanlist[i].key,
			catromanlist[i].code, catromanlist[i].str);
		if (n < 0) break;
	}

	qsort(romanlist, maxromanlist, sizeof(romantable), cmproman);
}
