dispdosdrive(no)
int no;
{
#  ifdef	HDDMOUNT
	char buf[strsize("HDD98 #offset=") + MAXCOLSCOMMA(3) + 1];
#  endif
	int i, len, w1, w2, width;

	if (no >= maxfdtype) {
		cputspace(MAXCUSTVAL);
		return(0);
	}
	width = (MAXCUSTVAL - 1) / 2;
	cputstr(width, fdtype[no].name);
	putsep();

	w1 = MAXCUSTVAL - 1 - width;
#  ifdef	HDDMOUNT
	if (!fdtype[no].cyl) {
		Xstrcpy(buf, "HDD");
		if (Xisupper(fdtype[no].head)) strcat(buf, "98");
		i = strlen(buf);
		VOID_C Xsnprintf(&(buf[i]), (int)sizeof(buf) - i,
			" #offset=%'Ld", fdtype[no].offset / fdtype[no].sect);
		cputstr(w1, buf);
	}
	else
#  endif
	{
		len = 0;
		for (i = 0; i < MEDIADESCRSIZ; i++) {
			w2 = strlen2(mediadescr[i].name);
			if (len < w2) len = w2;
		}

		w2 = (w1 - len) / 3 - 1;
		if (w2 <= 0) w2 = 1;
		VOID_C XXcprintf("%-*d", w2, (int)(fdtype[no].head));
		putsep();
		VOID_C XXcprintf("%-*d", w2, (int)(fdtype[no].sect));
		putsep();
		VOID_C XXcprintf("%-*d", w2, (int)(fdtype[no].cyl));
		putsep();

		for (i = 0; i < MEDIADESCRSIZ; i++) {
			if (fdtype[no].head == mediadescr[i].head
			&& fdtype[no].sect == mediadescr[i].sect
			&& fdtype[no].cyl == mediadescr[i].cyl)
				break;
		}
		w1 -= (w2 + 1) * 3;
		cputstr(w1, (i < MEDIADESCRSIZ) ? mediadescr[i].name : NULL);
	}
	len = strlen2(fdtype[no].name);
	if (len > --width) len = width;

	return(len);
}
