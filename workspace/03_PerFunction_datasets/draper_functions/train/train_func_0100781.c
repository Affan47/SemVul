check_reqs(stringlist_t *sl)
{
    stringlist_t *s;
    char *err = NULL, *p, sep = ':';
    size_t alloc = 0;

    while (sl != NULL) {
	s = sl;
	sl = sl->next;

	if (!script_require(parse_script, s->s)) {
	    if (!err) {
		alloc = 100;
		p = err = xmalloc(alloc);
		p += sprintf(p, "Unsupported feature(s) in \"require\"");
	    }
	    else if ((size_t) (p - err + strlen(s->s) + 5) > alloc) {
		alloc += 100;
		err = xrealloc(err, alloc);
		p = err + strlen(err);
	    }

	    p += sprintf(p, "%c \"%s\"", sep, s->s);
	    sep = ',';
	}

	free(s->s);
	free(s);
    }
    return err;
}
