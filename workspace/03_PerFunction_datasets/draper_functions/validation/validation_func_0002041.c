get_foreign_indent (void)
{
    const char *s;
    int i, n, ret = 100;

    for (i=0; i<foreign_n_lines; i++) {
	n = 0;
	s = foreign_lines[i];
	while (*s == ' ' || *s == '\t') {
	    n++;
	    s++;
	}
	if (n < ret) {
	    ret = n;
	}
    }

    return ret;
}
