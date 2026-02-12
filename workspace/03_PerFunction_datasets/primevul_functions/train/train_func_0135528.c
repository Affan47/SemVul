static void prepare_attr_stack(const char *path, int dirlen)
{
	struct attr_stack *elem, *info;
	int len;
	struct strbuf pathbuf;

	strbuf_init(&pathbuf, dirlen+2+strlen(GITATTRIBUTES_FILE));


	if (!attr_stack)
		bootstrap_attr_stack();


	info = attr_stack;
	attr_stack = info->prev;


	while (attr_stack && attr_stack->origin) {
		int namelen = strlen(attr_stack->origin);

		elem = attr_stack;
		if (namelen <= dirlen &&
		    !strncmp(elem->origin, path, namelen))
			break;

		debug_pop(elem);
		attr_stack = elem->prev;
		free_attr_elem(elem);
	}


	if (!is_bare_repository()) {
		while (1) {
			char *cp;

			len = strlen(attr_stack->origin);
			if (dirlen <= len)
				break;
			strbuf_reset(&pathbuf);
			strbuf_add(&pathbuf, path, dirlen);
			strbuf_addch(&pathbuf, '/');
			cp = strchr(pathbuf.buf + len + 1, '/');
			strcpy(cp + 1, GITATTRIBUTES_FILE);
			elem = read_attr(pathbuf.buf, 0);
			*cp = '\0';
			elem->origin = strdup(pathbuf.buf);
			elem->prev = attr_stack;
			attr_stack = elem;
			debug_push(elem);
		}
	}


	info->prev = attr_stack;
	attr_stack = info;
}
