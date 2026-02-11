MyXWidthToWChars(XFontStruct *font, const XChar2b *str, int len, int width)
{
    XCharStruct	*def;
    int		singlerow = (font->max_byte1 == 0);
    int		n;

    if (!font || width < 0)
	return 0;

    if (singlerow)
	CI_GET_DEFAULT_INFO_1D(font, def);
    else
	CI_GET_DEFAULT_INFO_2D(font, def);

    for (n = 0 ; n < len ; n++) {
	XCharStruct	*cs;

	if (singlerow) {
	    int	ch = (str[n].byte1 << 8) | str[n].byte2;

	    CI_GET_CHAR_INFO_1D(font, ch, def, cs);
	} else {
	    int	row = str[n].byte1;
	    int	col = str[n].byte2;

	    CI_GET_CHAR_INFO_2D(font, row, col, def, cs);
	}

	if (cs)
	    width -= cs->width;
	if (width < 0)
	    break;
    }

    return n;
}
