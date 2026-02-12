PJ_DEF(void) pj_scan_get_quotes(pj_scanner *scanner,
                                const char *begin_quote, const char *end_quote,
                                int qsize, pj_str_t *out)
{
    register char *s = scanner->curptr;
    int qpair = -1;
    int i;

    pj_assert(qsize > 0);


    for (i = 0; i < qsize; ++i) {
	if (*s == begin_quote[i]) {
	    qpair = i;
	    break;
	}
    }
    if (qpair == -1) {
	pj_scan_syntax_err(scanner);
	return;
    }
    ++s;


    do {

	while (PJ_SCAN_CHECK_EOF(s) && *s != '\n' && *s != end_quote[qpair]) {
	    ++s;
	}


	if (*s == end_quote[qpair]) {
	    if (*(s-1) == '\\') {
		char *q = s-2;
		char *r = s-2;

		while (r != scanner->begin && *r == '\\') {
		    --r;
		}

		if (((unsigned)(q-r) & 0x01) == 1) {
		    break;
		}
		++s;
	    } else {

		break;
	    }
	} else {

	    break;
	}
    } while (1);


    if (*s != end_quote[qpair]) {
	pj_scan_syntax_err(scanner);
	return;
    }
    ++s;

    pj_strset3(out, scanner->curptr, s);

    scanner->curptr = s;

    if (PJ_SCAN_IS_PROBABLY_SPACE(*s) && scanner->skip_ws) {
	pj_scan_skip_whitespace(scanner);
    }
}
