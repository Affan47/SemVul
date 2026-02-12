write_multiline(
    int x, int y,
    char *text,
    JUSTIFY hor,
    VERT_JUSTIFY vert,
    int angle,
    const char *font)
{
    struct termentry *t = term;
    char *p = text;

    if (!p)
	return;


    if (font && *font)
	(*t->set_font) (font);

    if (vert != JUST_TOP) {

	int lines = 0;
	while (*p) {
	    if (*p++ == '\n')
		++lines;
	}
	if (angle)
	    x -= (vert * lines * t->v_char) / 2;
	else
	    y += (vert * lines * t->v_char) / 2;
    }

    for (;;) {

	if ((text != NULL) && (p = strchr(text, '\n')) != NULL)
	    *p = 0;

	if ((*t->justify_text) (hor)) {
	    if (on_page(x, y))
		(*t->put_text) (x, y, text);
	} else {
	    int len = estimate_strlen(text, NULL);
	    int hfix, vfix;

	    if (angle == 0) {
		hfix = hor * t->h_char * len / 2;
		vfix = 0;
	    } else {

		hfix = hor * t->h_char * len * cos(angle * DEG2RAD) / 2 + 0.5;
		vfix = hor * t->v_char * len * sin(angle * DEG2RAD) / 2 + 0.5;
	    }
		if (on_page(x - hfix, y - vfix))
		    (*t->put_text) (x - hfix, y - vfix, text);
	}
	if (angle == 90 || angle == TEXT_VERTICAL)
	    x += t->v_char;
	else if (angle == -90 || angle == -TEXT_VERTICAL)
	    x -= t->v_char;
	else
	    y -= t->v_char;

	if (!p)
	    break;
	else {

	    *p = '\n';
	}

	text = p + 1;
    }

    if (font && *font)
	(*t->set_font) ("");

}
