pretty_display_numeric (cob_field *f, FILE *fp)
{
	unsigned char	*p;
	int		i;
	int		digits;
	int		scale;
	int		size;
	cob_field_attr	attr;
	cob_field	temp;
	unsigned char	pic[64];
	unsigned char	data[256];

	if (f->size == 0) {
		return;
	}


		digits = COB_FIELD_DIGITS (f);


	scale = COB_FIELD_SCALE (f);
	size = (digits + (COB_FIELD_HAVE_SIGN (f) ? 1 : 0)
		+ (scale > 0 ? 1 : 0));
	p = pic;
	temp.size = size;
	temp.data = data;
	temp.attr = &attr;
	COB_ATTR_INIT (COB_TYPE_NUMERIC_EDITED, digits, scale, 0, (char *)pic);
	memset (pic, 0, sizeof (pic));
	memset (data, 0, sizeof (data));
	if (COB_FIELD_HAVE_SIGN (f)) {
		*p++ = '+';
		i = 1;
		memcpy (p, (unsigned char *)&i, sizeof(int));
		p += sizeof(int);
	}
	if (scale > 0) {
		*p++ = '9';
		i = digits - scale;
		memcpy (p, (unsigned char *)&i, sizeof(int));
		p += sizeof(int);
		*p++ = cob_current_module->decimal_point;
		i = 1;
		memcpy (p, (unsigned char *)&i, sizeof(int));
		p += sizeof(int);
		*p++ = '9';
		i = scale;
		memcpy (p, (unsigned char *)&i, sizeof(int));
		p += sizeof(int);
	} else {
		*p++ = '9';
		i = digits;
		memcpy (p, (unsigned char *)&i, sizeof(int));
		p += sizeof(int);
	}

	cob_move (f, &temp);
	for (i = 0; i < size; ++i) {
		putc (data[i], fp);
	}
}
