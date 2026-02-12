_nc_capcmp(const char *s, const char *t)

{
    bool ok_s = VALID_STRING(s);
    bool ok_t = VALID_STRING(t);

    if (ok_s && ok_t) {
	for (;;) {
	    if (s[0] == '$' && s[1] == '<') {
		for (s += 2;; s++) {
		    if (!(isdigit(UChar(*s))
			  || *s == '.'
			  || *s == '*'
			  || *s == '/'
			  || *s == '>')) {
			break;
		    }
		}
	    }

	    if (t[0] == '$' && t[1] == '<') {
		for (t += 2;; t++) {
		    if (!(isdigit(UChar(*t))
			  || *t == '.'
			  || *t == '*'
			  || *t == '/'
			  || *t == '>')) {
			break;
		    }
		}
	    }


	    if (*s == '\0' && *t == '\0')
		return (0);

	    if (*s != *t)
		return (*t - *s);


	    s++, t++;
	}
    } else if (ok_s || ok_t) {
	return 1;
    }
    return 0;
}
