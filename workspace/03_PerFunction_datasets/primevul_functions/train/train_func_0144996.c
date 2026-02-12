static char *theme_format_expand_abstract(THEME_REC *theme, const char **formatp,
                                          theme_rm_col *last_fg, theme_rm_col *last_bg, int flags,
                                          GTree *block_list)
{
	GString *str;
	const char *p, *format;
	char *abstract, *data, *ret;
	theme_rm_col default_fg, default_bg;
	int len;

	format = *formatp;
	default_fg = *last_fg;
	default_bg = *last_bg;


	p = format;
	while (*p != '\0' && *p != ' ' &&
	       *p != '{' && *p != '}') p++;
	if (*p == '\0' || p == format)
		return NULL;

	len = (int) (p-format);
	abstract = g_strndup(format, len);


	if (*p == ' ') {
		len++;
		if ((flags & EXPAND_FLAG_IGNORE_EMPTY) && data_is_empty(&p)) {
			*formatp = p;
			g_free(abstract);
			return NULL;
		}
	}
	*formatp = format+len;

	if (block_list == NULL) {
		block_list = g_tree_new_full((GCompareDataFunc) g_strcmp0, NULL, g_free, NULL);
	} else {
		g_tree_ref(block_list);
	}


	data = g_hash_table_lookup(theme->abstracts, abstract);
	if (data == NULL || g_tree_lookup(block_list, abstract) != NULL) {

		data = "$0-";
		g_free(abstract);
	} else {
		g_tree_insert(block_list, abstract, abstract);
	}
	abstract = g_strdup(data);


	data = theme_format_expand_get(theme, formatp);
	len = strlen(data);

	if (len > 1 && i_isdigit(data[len-1]) && data[len-2] == '$') {


                char digit, *tmp;

		tmp = data;
		digit = tmp[len-1];
		tmp[len-1] = '\0';

		data = g_strdup_printf("%s{%c}", tmp, digit);
		g_free(tmp);
	}

	ret = parse_special_string(abstract, NULL, NULL, data, NULL,
				   PARSE_FLAG_ONLY_ARGS);
	g_free(abstract);
        g_free(data);
	str = g_string_new(NULL);
	p = ret;
	while (*p != '\0') {
		if (*p == '\\' && p[1] != '\0') {
			int chr;
			p++;
			chr = expand_escape(&p);
			g_string_append_c(str, chr != -1 ? chr : *p);
		} else
			g_string_append_c(str, *p);
		p++;
	}
	g_free(ret);
	abstract = str->str;
	g_string_free(str, FALSE);


	p = abstract;
	ret = theme_format_expand_data_rec(theme, &p, default_fg, default_bg, last_fg, last_bg,
	                                   flags | EXPAND_FLAG_LASTCOLOR_ARG, block_list);
	g_free(abstract);
	g_tree_unref(block_list);
	return ret;
}
