create_history(const char *dst, expression * e)
{
    static int WIDTH = RECORD_LEN - 12;
    struct History hist;
    char *expr = format_expression(e);
    char *p = expr;
    int len = strlen(expr);
    int i;

    G_short_history((char *)dst, "raster", &hist);

    for (i = 0; i < MAXEDLINES; i++) {
	int n;

	if (!len)
	    break;

	if (len > WIDTH) {
	    for (n = WIDTH; n > 0 && p[n] != ' '; n--) ;

	    if (n <= 0)
		n = WIDTH;
	    else
		n++;
	}
	else
	    n = len;

	memcpy(hist.edhist[i], p, n);
	hist.edhist[i][n] = '\0';

	p += n;
	len -= n;
    }

    hist.edlinecnt = i;

    G_write_history((char *)dst, &hist);

    G_free(expr);
}
