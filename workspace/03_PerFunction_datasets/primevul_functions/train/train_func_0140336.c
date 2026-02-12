static void gch_build(struct SYMBOL *s)
{
	struct gch *gch;
	char *p, *q, antype, sep;
	float w, h_ann, h_gch, y_above, y_below, y_left, y_right;
	float xspc;
	int l, ix, box, gch_place;

	if (s->posit.gch == SL_HIDDEN)
		return;
	s->gch = getarena(sizeof *s->gch * MAXGCH);
	memset(s->gch, 0, sizeof *s->gch * MAXGCH);

	if (cfmt.capo)
		gch_capo(s);
	if (curvoice->transpose != 0)
		gch_transpose(s);


	gch_place = s->posit.gch == SL_BELOW ? -1 : 1;
	h_gch = cfmt.font_tb[cfmt.gcf].size;
	h_ann = cfmt.font_tb[cfmt.anf].size;
	y_above = y_below = y_left = y_right = 0;
	box = cfmt.gchordbox;
	p = s->text;
	gch = s->gch;
	sep = '\n';
	antype = 'g';
	for (;;) {
		if (sep != 'n' && strchr("^_<>@", *p)) {
			gch->font = cfmt.anf;
			antype = *p++;
			if (antype == '@') {
				int n;
				float xo, yo;

				if (sscanf(p, "%f,%f%n", &xo, &yo, &n) != 2) {
					error(1, s, "Error in annotation \"@\"");
				} else {
					p += n;
					if (*p == ' ')
						p++;
					gch->x = xo;
					gch->y = yo;
				}
			}
		} else if (sep == '\n') {
			gch->font = cfmt.gcf;
			gch->box = box;
			antype = 'g';
		} else {
			gch->font = (gch - 1)->font;
			gch->box = (gch - 1)->box;
		}
		gch->type = antype;
		switch (antype) {
		default:
			if (gch_place < 0)
				break;
			y_above += h_gch;
			if (box)
				y_above += 2;
			break;
		case '^':
			y_above += h_ann;
			break;
		case '_':
			break;
		case '<':
			y_left += h_ann * 0.5;
			break;
		case '>':
			y_right += h_ann * 0.5;
			break;
		case '@':
			if (gch->x == 0 && gch->y == 0
			 && gch != s->gch
			 && s->gch->type == '@') {
				gch->x = (gch - 1)->x;
				gch->y = (gch - 1)->y - h_ann;
			}
			break;
		}
		gch->idx = p - s->text;
		for (;;) {
			switch (*p) {
			default:
				p++;
				continue;
			case '\\':
				p++;
				if (*p == 'n') {
					p[-1] = '\0';
					break;
				}
				p++;
				continue;
			case '&':
				for (;;) {
					switch (*p) {
					default:
						p++;
						continue;
					case ';':
						p++;
					case '\0':
					case '\n':
					case '\\':
						break;
					}
					break;
				}
				continue;
			case '\0':
			case ';':
			case '\n':
				break;
			}
			break;
		}
		sep = *p;
		if (sep == '\0')
			break;
		*p++ = '\0';
		gch++;
		if (gch - s->gch >= MAXGCH) {
			error(1, s, "Too many guitar chords / annotations");
			break;
		}
	}


	for (ix = 0, gch = s->gch; ix < MAXGCH; ix++, gch++) {
		if (gch->type == '\0')
			break;
		if (gch->type != 'g')
			continue;
		p = s->text + gch->idx;
		q = p;
		for (; *p != '\0'; p++) {
			switch (*p) {
			case '#':
			case 'b':
			case '=':
				if (p == q
				 || (p != q + 1
				  && p[-1] == '\\'))
					break;


				switch (*p) {
				case '#':
					*p = 0x01;
					break;
				case 'b':
					*p = 0x02;
					break;
				default:

					*p = 0x03;
					break;
				}
				if (p[-1] == '\\') {
					p--;
					l = strlen(p);
					memmove(p, p + 1, l);
				}
				break;
			case ' ':
			case '/':
				q = p + 1;
				break;
			}
		}
	}


	for (ix = 0, gch = s->gch; ix < MAXGCH; ix++, gch++) {
		if (gch->type == '\0')
			break;
		if (gch->type == '@')
			continue;
		p = s->text + gch->idx;
		str_font(gch->font);
		w = tex_str(p);
		gch->w = w;
		switch (gch->type) {
		case '_':
			xspc = w * GCHPRE;
			if (xspc > 8)
				xspc = 8;
			gch->x = -xspc;
			y_below -= h_ann;
			gch->y = y_below;
			break;
		case '^':
			xspc = w * GCHPRE;
			if (xspc > 8)
				xspc = 8;
			gch->x = -xspc;
			y_above -= h_ann;
			gch->y = y_above;
			break;
		default:
			xspc = w * GCHPRE;
			if (xspc > 8)
				xspc = 8;
			gch->x = -xspc;
			if (gch_place < 0) {
				y_below -= h_gch;
				gch->y = y_below;
				if (box) {
					y_below -= 2;
					gch->y -= 1;
				}
			} else {
				y_above -= h_gch;
				gch->y = y_above;
				if (box) {
					y_above -= 2;
					gch->y -= 1;
				}
			}
			break;
		case '<':
			gch->x = -(w + 6);
			y_left -= h_ann;
			gch->y = y_left;
			break;
		case '>':
			gch->x = 6;
			y_right -= h_ann;
			gch->y = y_right;
			break;
		}
	}
}
