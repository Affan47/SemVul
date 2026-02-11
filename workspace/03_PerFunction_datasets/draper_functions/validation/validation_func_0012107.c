unmungestr(const char *in)
{
    char *out, *ret;
    out = ret = snewn(strlen(in)+1, char);
    while (*in) {
	if (*in == '%' && in[1] && in[2]) {
	    int i, j;

	    i = in[1] - '0';
	    i -= (i > 9 ? 7 : 0);
	    j = in[2] - '0';
	    j -= (j > 9 ? 7 : 0);

	    *out++ = (i << 4) + j;
	    in += 3;
	} else {
	    *out++ = *in++;
	}
    }
    *out = '\0';
    return ret;
}
