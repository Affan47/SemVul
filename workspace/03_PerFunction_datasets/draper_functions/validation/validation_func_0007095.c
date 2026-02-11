find_name(const char *line, char *def, int p_value, int terminate)
{
	int len;
	const char *start = line;

	if (*line == '"') {
		struct strbuf name = STRBUF_INIT;


		if (!unquote_c_style(&name, line, NULL)) {
			char *cp;

			for (cp = name.buf; p_value; p_value--) {
				cp = strchr(cp, '/');
				if (!cp)
					break;
				cp++;
			}
			if (cp) {


				strbuf_remove(&name, 0, cp - name.buf);
				free(def);
				if (root)
					strbuf_insert(&name, 0, root, root_len);
				return strbuf_detach(&name, NULL);
			}
		}
		strbuf_release(&name);
	}

	for (;;) {
		char c = *line;

		if (isspace(c)) {
			if (c == '\n')
				break;
			if (name_terminate(start, line-start, c, terminate))
				break;
		}
		line++;
		if (c == '/' && !--p_value)
			start = line;
	}
	if (!start)
		return def;
	len = line - start;
	if (!len)
		return def;


	if (def) {
		int deflen = strlen(def);
		if (deflen < len && !strncmp(start, def, deflen))
			return def;
		free(def);
	}

	if (root) {
		char *ret = xmalloc(root_len + len + 1);
		strcpy(ret, root);
		memcpy(ret + root_len, start, len);
		ret[root_len + len] = '\0';
		return ret;
	}

	return xmemdupz(start, len);
}
