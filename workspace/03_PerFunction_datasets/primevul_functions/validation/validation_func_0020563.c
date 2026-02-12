readfile_linenr(
    linenr_T	linecnt,
    char_u	*p,
    char_u	*endp)
{
    char_u	*s;
    linenr_T	lnum;

    lnum = curbuf->b_ml.ml_line_count - linecnt + 1;
    for (s = p; s < endp; ++s)
	if (*s == '\n')
	    ++lnum;
    return lnum;
}
