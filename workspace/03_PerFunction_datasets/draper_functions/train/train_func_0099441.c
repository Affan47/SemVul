rdcmnt(fp) FILE *fp; {
    int c,star,prcnt;
    prcnt = star = 0;
    while (!((c = getc(fp)) == '/' && star)) {
	if (c == EOF || (prcnt && c == '%')) fatal("Unterminated comment");
	prcnt = (c == '%');
	star = (c == '*');
	if (c == '\n') lines++;
    }
}
