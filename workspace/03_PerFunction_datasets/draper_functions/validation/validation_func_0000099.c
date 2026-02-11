initial(infp,outfp) FILE *infp, *outfp; {
    int c;
    char wordbuf[MAXWORD];
    while ((c = getc(infp)) != EOF) {
	if (c == '%') {
	    rdword(infp,wordbuf);
	    if (strcmp(wordbuf,"states") == 0)
	      rdstates(infp,outfp);
	    else if (strcmp(wordbuf,"%") == 0) return;
	    else fprintf(outfp,"%%%s",wordbuf);
	}
	else putc(c,outfp);
	if (c == '\n') lines++;
    }
}
