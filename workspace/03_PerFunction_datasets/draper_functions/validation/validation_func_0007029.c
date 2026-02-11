tab_snprint_head(char *line, int len,
			    struct col_format *cfmt, int ncol)
{
	int i;
	int p = 0, ret = 0;
	char buf[64];
	int w;

	for (i=0; i<ncol; i++) {
		w = cfmt[i].width;
		if (i==0) {
			w--;
			p += string_field(line + p, len - 1, 2, "#");
			if (p >= len)
				break;
		}
		switch(cfmt[i].type) {
		case SYM_SMAG:
			snprintf(buf, 63, "s(%s)", (char *)cfmt[i].data);
			ret = string_field(line + p, len - p, w + 1, buf);
			break;
		case SYM_IMAG:
			snprintf(buf, 63, "i(%s)", (char *)cfmt[i].data);
			ret = string_field(line + p, len - p, w + 1, buf);
			break;
		case SYM_SERR:
			snprintf(buf, 63, "se(%s)", (char *)cfmt[i].data);
			ret = string_field(line + p, len - p, w + 1, buf);
			break;
		case SYM_IERR:
			snprintf(buf, 63, "ie(%s)", (char *)cfmt[i].data);
			ret = string_field(line + p, len - p, w + 1, buf);
			break;
		default:
			if (i >= 1)
				ret = string_field(line + p, len - p, w + 1,
						   symname[cfmt[i].type]);
			else
				ret = string_field(line + p, len - p, w,
						   symname[cfmt[i].type]);
			break;
		}
		if (p > 4)
			line[p-1]='|';
		p += ret;
		if (p >= len)
			break;
	}
	return p;
}
