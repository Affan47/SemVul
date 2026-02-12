output_colour(int colour, int fg_bg, int use_tc, int truecol, char *buf)
{
    int atrlen = 3, len;
    char *ptr = buf;
    if (buf) {
	strcpy(ptr, fg_bg == COL_SEQ_FG ? "fg=" : "bg=");
	ptr += 3;
    }
    if (truecol) {

	atrlen += buf ? sprintf(ptr, "#%02x%02x%02x", colour >> 16,
		(colour >> 8) & 0xff, colour & 0xff) : 7;


    } else if (use_tc || colour > 7) {
	char digbuf[DIGBUFSIZE];
	sprintf(digbuf, "%d", colour);
	len = strlen(digbuf);
	atrlen += len;
	if (buf)
	    strcpy(ptr, digbuf);
    } else {
	len = strlen(ansi_colours[colour]);
	atrlen += len;
	if (buf)
	    strcpy(ptr, ansi_colours[colour]);
    }

    return atrlen;
}
